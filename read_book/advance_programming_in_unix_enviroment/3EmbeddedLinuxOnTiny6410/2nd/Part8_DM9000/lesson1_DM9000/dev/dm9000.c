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
//�ж����μĴ���
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
		DM_ADD = reg;//���Ĵ�����ַд��INDEX�˿�
		DM_DAT = data;//������д��DATA�˿ڣ���д���Ĵ���
}

u8 dm9000_reg_read(u16 reg)
{
		DM_ADD = reg;
		
		return DM_DAT;//�����ݴӼĴ����ж��� 
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



void cs_init()//Ƭѡʹ��nCS1������BANK1
{
    //���ÿ����������߿��
    SROM_BW|= 1<<4;
    
/*
DataWidth1 [4] Data bus width control for Memory Bank1
0 = 8-bit 1 = 16-bit
*/    

		//����ʱ��
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
void int_init()//�ж�Դʹ��EINT7
{
	//���ŵ�GPIO����
		GPNCON |= GPNCON &(~(0x3<<14));//������
	  GPNCON |= GPNCON |(0b10<<14);
/* 
GPN7 [15:14] 00 = Input 01 = Output
10 = Ext. Interrupt[7] 11 = Key pad ROW[7]
*/	 
  //�жϴ�����ʽ����
     /*EINT0CON0 = EINT0CON0 & (~(0x3<<12));//������
     EINT0CON0 = EINT0CON0 | (0x1<<12);   //Falling edge triggered
/*
	EINT7, 6 [14:12] Setting the signaling method of the EINT7 and EINT6.
	000 = Low level 001 = High level
	01x = Falling edge triggered 10x = Rising edge triggered
	11x = Both edge triggered


		/*�޸��ж����μĴ���EINT0MASK
	    EINT0MASK = 0;//ȫ���ж϶�������
	
		/*ʹ���ж��������ƼĴ���EINT0MASK
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


	//���жϷ������ĵ�ַ���͵��ж�������ַ�Ĵ���VECTADDR��
			DM9000VIC0VECTADDR = (int)DM9000_isr;

   //EINT0PEND����
    //EINT0PEND |= (1<<7);
// Each bit is cleared by writing "1"
   
   //�����жϵĿ���
		__asm__(
						//6410Ҳ֧�ַ������ж�ģʽ������������ص�cp15�Ĵ����ĵ�24λ����������ܴ�
						"mrc p15,0,r0,c1,c0,0\n"
						"orr r0,r0,#(1<<24)\n"
						"mcr p15,0,r0,c1,c0,0\n"
						
						//�����ж�,������start.S�а��жϸ��ر��ˣ���������Ҫ���¿���
						"mrs r0,cpsr\n"			//�ȶ�
						"bic r0,r0,#0x80\n" //����λ��cpsr��bit7 �ǿ���irq disable��
						"msr cpsr_c,r0\n"		//���д�룬ֻдcontrol��cpsr_c
						:
						:
		);
		
	
}*/


void dm9000_init()
{
	  u32 i;
	  //����Ƭѡ
	  cs_init();
	  
	  //�жϳ�ʼ��
	  //int_init();
	
		/* RESET device */
		dm9000_reset();
		
    /*����dm9000*/
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
		for (i = 0; i < 6; i++)//���������ַ
        dm9000_reg_write(DM9000_PAR+i, mac_addr[i]);
		
		/* Activate DM9000 */
		
			dm9000_reg_write(DM9000_RCR, RCR_DIS_LONG | RCR_DIS_CRC | RCR_RXEN);
	
	/* Enable TX/RX interrupt mask */
	   dm9000_reg_write(DM9000_IMR, IMR_PAR);
		
	}
	
void dm9000_tx(u8 *data,u32 length)
{
	u32 i;
    
    /*��ֹ�ж�*/
    dm9000_reg_write(DM9000_IMR,0x80);
    
    /*д�뷢�����ݵĳ���*/
    dm9000_reg_write(DM9000_TXPLL, length & 0xff);
    dm9000_reg_write(DM9000_TXPLH, (length >> 8) & 0xff);
    
    /*д������͵�����*/
    DM_ADD = DM9000_MWCMD;
   
    for(i=0;i<length;i+=2)
    {
    	DM_DAT = data[i] | (data[i+1]<<8);
    }
    
    /*��������*/
    dm9000_reg_write(DM9000_TCR, TCR_TXREQ); 
    
    /*�ȴ����ͽ���*/
    while(1)
    {
       u8 status;
       status = dm9000_reg_read(DM9000_TCR);
       if((status&0x01)==0x00)
           break;	
    }
    
    /*�������״̬*/
    dm9000_reg_write(DM9000_NSR,0x2c);
    
    /*�ָ��ж�ʹ��*/
    dm9000_reg_write(DM9000_IMR,0x81);
	

	}

#define PTK_MAX_LEN 1522//һ����̫���İ���󳤶Ⱦ���1522

u32 dm9000_rx(u8 *data)
{
    u8 status,len;
    u16 tmp;
    u32 i;
    
    /*�ж��Ƿ�����жϣ������*/
    if(dm9000_reg_read(DM9000_ISR) & 0x01)
        dm9000_reg_write(DM9000_ISR,0x01);
    else
        return 0;
        
    /*�ն�*/
    dm9000_reg_read(DM9000_MRCMDX);
    
    /*��ȡ״̬*/
    status = dm9000_reg_read(DM9000_MRCMD);
    
    /*��ȡ������*/
    len = DM_DAT;
    
    /*��ȡ������*/
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
				arp_request();//���Ϸ��������
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

