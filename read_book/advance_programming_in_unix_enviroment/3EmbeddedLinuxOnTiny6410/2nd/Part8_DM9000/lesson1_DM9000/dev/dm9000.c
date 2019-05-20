/*
@Platform: Friendly Arm tiny6410
@CPU: S3C6410
@Function: Bootloader0 ,init cpu 
@Written by Armstrong Wall
@Start wrirte date: 2016.3.25
@Daily: 		2016.3.25  Finish DM9000
*/


#include "dm9000.h"
#include "printf.h"
#include "arp.h"


#define SROM_BW           (*((volatile unsigned long *)0x70000000))
//SROM Bus width & wait control
#define SROM_BC1          (*((volatile unsigned long *)0x70000008))
//  R/W SROM Bank1 control register

#define EINT0CON0         (*((volatile unsigned long *)0x7F008900))
//  R/W External Interrupt 0(Group0) Configuration Register 0

#define EINT0MASK          (*((volatile unsigned long *)0x7F008920))
//中断屏蔽寄存器
#define VIC0INTENABLE 		 (*((volatile unsigned long *)0x71200010))
//VECTORED INTERRUPT CONTROLLERS
#define EINT0PEND 	   	   (*((volatile unsigned long *)0x7F008924))
//R/W External Interrupt 0(Group0) Pending Register

#define VIC0ADDRESS				 (*((volatile unsigned long *)0x71200F00)) //Vector Address Register (VIC0)


#define DM9KS_BASE_ADDR_ETH0     0x18000000
#define DM_ADD  (*((volatile short *) 0x18000000))
#define DM_DAT  (*((volatile short *) 0x18000004))

int dm9000_flag = 0;

void DM9000_isr();

void dm9000_reg_write(u16 reg,u16 data)
{
		DM_ADD = reg;//将寄存器地址写到INDEX端口
		DM_DAT = data;//将数据写到DATA端口，即写进寄存器
}

u8 dm9000_reg_read(u16 reg)
{
		DM_ADD = reg;
		
		return DM_DAT;//将数据从寄存器中读出 
	}
	
void dm9000_reset()
{
	/* DEBUG: Make all GPIO0 outputs, all others inputs */
    dm9000_reg_write(DM9000_GPCR, GPCR_GPIO0_OUT);
    
  /* Step 1: Power internal PHY by writing 0 to GPIO0 pin */
    dm9000_reg_write(DM9000_GPR, 0);	

  /* Step 2: Software reset */    
    dm9000_reg_write(DM9000_NCR, (NCR_LBK_INT_MAC | NCR_RST));
    
    
    dm9000_reg_write(DM9000_NCR, 0);
    
    
    dm9000_reg_write(DM9000_NCR, (NCR_LBK_INT_MAC | NCR_RST));
    dm9000_reg_write(DM9000_NCR, 0);
}

void dm9000_probe(void)
{
	u32 id_val;
	id_val = dm9000_reg_read(DM9000_VIDL);
	id_val |= dm9000_reg_read(DM9000_VIDH) << 8;
	id_val |= dm9000_reg_read(DM9000_PIDL) << 16;
	id_val |= dm9000_reg_read(DM9000_PIDH) << 24;
	if (id_val == DM9000_ID) {
		printf("dm9000 is found !\n");
		return ;
	} else {
		printf("dm9000 is not found !\n");
		return ;
	}
	
}



void cs_init()//片选使用nCS1，属于BANK1
{
    //设置控制数据总线宽度
    SROM_BW|= 1<<4;
    
/*
DataWidth1 [4] Data bus width control for Memory Bank1
0 = 8-bit 1 = 16-bit
*/    

		//设置时序
		SROM_BC1 = (0x10<<28) | (0x10<<24)
		          |(0x10<<16)	| (0x10<<12)
		          |(0x10<<8)	| (0x10<<4)| (0x00<<0);
/*
#define B1_Tacs			0x10	  2clk 
#define B1_Tcos			0x10	  2clk 
#define B1_Tacc			0x10	  3clk 
#define B1_Tcoh			0x10	  2clk 
#define B1_Tah			0x10	  2clk  
#define B1_Tacp			0x10    2clk 
#define B1_PMC			0x00	  normal  

*/  
}

/*
void int_init()//中断源使用EINT7
{
	//引脚的GPIO配置
		GPNCON |= GPNCON &(~(0x3<<14));//先清零
	  GPNCON |= GPNCON |(0b10<<14);
/* 
GPN7 [15:14] 00 = Input 01 = Output
10 = Ext. Interrupt[7] 11 = Key pad ROW[7]
*/	 
  //中断触发方式设置
     /*EINT0CON0 = EINT0CON0 & (~(0x3<<12));//先清零
     EINT0CON0 = EINT0CON0 | (0x1<<12);   //Falling edge triggered
/*
	EINT7, 6 [14:12] Setting the signaling method of the EINT7 and EINT6.
	000 = Low level 001 = High level
	01x = Falling edge triggered 10x = Rising edge triggered
	11x = Both edge triggered


		/*修改中断屏蔽寄存器EINT0MASK
	    EINT0MASK = 0;//全部中断都不屏蔽
	
		/*使能中断向量控制寄存器EINT0MASK
	    VIC0INTENABLE |= 0x2;
/*
Write:
0 = no effect
1 = interrupt enabled.
On reset, all interrupts are disabled.
There is one bit of the register for each interrupt source


The S3C6410X supports 64 interrupt sources as shown in the table below
Int. No.      Sources              Description   Group


1 INT_EINT1   External interrupt   4 ~ 11        VIC0
0 INT_EINT0   External interrupt   0 ~ 3         VIC0

enabled EINT7, so set bit2 to 1,  so VIC0INTENABLE |= 0x2;  


	//将中断服务函数的地址传送到中断向量地址寄存器VECTADDR中
			DM9000VIC0VECTADDR = (int)DM9000_isr;

   //EINT0PEND清零
    //EINT0PEND |= (1<<7);
// Each bit is cleared by writing "1"
   
   //打开总中断的控制
		__asm__(
						//6410也支持非向量中断模式，所以设置相关的cp15寄存器的第24位，把这个功能打开
						"mrc p15,0,r0,c1,c0,0\n"
						"orr r0,r0,#(1<<24)\n"
						"mcr p15,0,r0,c1,c0,0\n"
						
						//开总中断,由于在start.S中把中断给关闭了，所以这里要重新开启
						"mrs r0,cpsr\n"			//先读
						"bic r0,r0,#0x80\n" //再置位，cpsr的bit7 是控制irq disable的
						"msr cpsr_c,r0\n"		//最后写入，只写control域cpsr_c
						:
						:
		);
		
	
}*/


void dm9000_init()
{
	  u32 i;
	  //设置片选
	  cs_init();
	  
	  //中断初始化
	  //int_init();
	
		/* RESET device */
		dm9000_reset();
		
    /*捕获dm9000*/
    dm9000_probe();
    
    printf("dm9000_probe ok");
   
		/* MAC init */
		  /* Program operating register, only internal phy supported */
		dm9000_reg_write(DM9000_NCR, 0x0);
		/* TX Polling clear */
		dm9000_reg_write(DM9000_TCR, 0);
		/* Less 3Kb, 200us */
		dm9000_reg_write(DM9000_BPTR, BPTR_BPHW(3) | BPTR_JPT_600US);
		/* Flow Control : High/Low Water */
		dm9000_reg_write(DM9000_FCTR, FCTR_HWOT(3) | FCTR_LWOT(8));
		/* SH FIXME: This looks strange! Flow Control */
		dm9000_reg_write(DM9000_FCR, 0x0);
		/* Special Mode */
		dm9000_reg_write(DM9000_SMCR, 0);
		/* clear TX status */
		dm9000_reg_write(DM9000_NSR, NSR_WAKEST | NSR_TX2END | NSR_TX1END);
		/* Clear interrupt status */
		dm9000_reg_write(DM9000_ISR, ISR_ROOS | ISR_ROS | ISR_PTS | ISR_PRS);
		
		
		/* fill device MAC address registers */
		for (i = 0; i < 6; i++)//设置物理地址
        dm9000_reg_write(DM9000_PAR+i, mac_addr[i]);
		
		/* Activate DM9000 */
		
			dm9000_reg_write(DM9000_RCR, RCR_DIS_LONG | RCR_DIS_CRC | RCR_RXEN);
	
	/* Enable TX/RX interrupt mask */
	   dm9000_reg_write(DM9000_IMR, IMR_PAR);
		
	}
	
void dm9000_tx(u8 *data,u32 length)
{
	u32 i;
    
    /*禁止中断*/
    dm9000_reg_write(DM9000_IMR,0x80);
    
    /*写入发送数据的长度*/
    dm9000_reg_write(DM9000_TXPLL, length & 0xff);
    dm9000_reg_write(DM9000_TXPLH, (length >> 8) & 0xff);
    
    /*写入待发送的数据*/
    DM_ADD = DM9000_MWCMD;
   
    for(i=0;i<length;i+=2)
    {
    	DM_DAT = data[i] | (data[i+1]<<8);
    }
    
    /*启动发送*/
    dm9000_reg_write(DM9000_TCR, TCR_TXREQ); 
    
    /*等待发送结束*/
    while(1)
    {
       u8 status;
       status = dm9000_reg_read(DM9000_TCR);
       if((status&0x01)==0x00)
           break;	
    }
    
    /*清除发送状态*/
    dm9000_reg_write(DM9000_NSR,0x2c);
    
    /*恢复中断使能*/
    dm9000_reg_write(DM9000_IMR,0x81);
	

	}

#define PTK_MAX_LEN 1522//一个以太网的包最大长度就是1522

u32 dm9000_rx(u8 *data)
{
    u8 status,len;
    u16 tmp;
    u32 i;
    
    /*判断是否产生中断，且清除*/
    if(dm9000_reg_read(DM9000_ISR) & 0x01)
        dm9000_reg_write(DM9000_ISR,0x01);
    else
        return 0;
        
    /*空读*/
    dm9000_reg_read(DM9000_MRCMDX);
    
    /*读取状态*/
    status = dm9000_reg_read(DM9000_MRCMD);
    
    /*读取包长度*/
    len = DM_DAT;
    
    /*读取包数据*/
    if(len<PTK_MAX_LEN)
    {
       for(i=0;i<len;i+=2)
       {
           tmp = DM_DAT;
           data[i] = tmp & 0x0ff;
           data[i+1] = (tmp>>8)&0x0ff;
       }
    }
    
    return len;
}

int i = 0;

void dm9000_arp()
{
    while(1)
    {
				arp_request();//不断发送请求包
				printf("\nsend ok\n\r");
				if(i>=0 && i<=100 )
					{
							led_on();
						}
			  else
			  	{
			  		  led_off();
			  		}
			  		
			  i++;
			  
			  if(i==200)
					{
						  i =0;
			  		}
			 
			
    	}
}

