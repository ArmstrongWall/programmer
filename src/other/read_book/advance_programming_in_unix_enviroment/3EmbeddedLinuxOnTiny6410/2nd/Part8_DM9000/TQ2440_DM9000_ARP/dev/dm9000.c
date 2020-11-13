#include "dm9000.h"
#include "arp.h"

#define DM_ADD (*((volatile unsigned short *)0x20000300))
#define DM_DAT (*((volatile unsigned short *)0x20000304))

#define GPFCON    (*(volatile unsigned *)0x56000050)	//Port F control
#define EXTINT0   (*(volatile unsigned *)0x56000088)	//External interrupt control register 0
#define EINTMASK  (*(volatile unsigned *)0x560000a4)	//External interrupt mask
#define SRCPND     (*(volatile unsigned *)0x4a000000)	//Interrupt request status
#define INTPND     (*(volatile unsigned *)0x4a000010)	//Interrupt request status
#define INTMSK     (*(volatile unsigned *)0x4a000008)	//Interrupt mask control
#define EINTPEND  (*(volatile unsigned *)0x560000a8)	//External interrupt pending

#define BWSCON    (*(volatile unsigned *)0x48000000)	//Bus width & wait status
#define BANKCON4  (*(volatile unsigned *)0x48000014)	//BANK4 control


u8 *buffer = &arpbuf;

u8 host_mac_addr[6] = {0xff,0xff,0xff,0xff,0xff,0xff};
u8 mac_addr[6] = {9,8,7,6,5,4};
u8 ip_addr[4] = {192,168,1,30};
u8 host_ip_addr[4] = {192,168,1,100};
u16 packet_len;


void cs_init()
{
	BWSCON = BWSCON & (~(0x3<<16));
	BWSCON = BWSCON |(0x1<<16);
	BANKCON4 = (0x0<<13)|(0x0<<11)|(0x7<<8)|(0x1<<6)|(0x0<<4)|(0x0<<2)|(0x0<<0);
}

void int_init()
{
	GPFCON = GPFCON &(~(0x3<<14));
	GPFCON = GPFCON |(0x2<<14);
	EXTINT0 = EXTINT0 & (~(0x7<<28));
	EXTINT0 = EXTINT0 | (0x1<<28);
	INTMSK = INTMSK &(~(1<<4));
	EINTMASK = EINTMASK & (~(0x1<<7));
	SRCPND = (1<<4);
	INTPND = (1<<4);
}

void dm9000_reg_write(u16 reg,u16 data)
{
    DM_ADD = reg;	
    DM_DAT = data;	
}

u8 dm9000_reg_read(u16 reg)
{
    DM_ADD = reg;
    return DM_DAT;	
}

void dm9000_reset()
{
    dm9000_reg_write(DM9000_GPCR, GPCR_GPIO0_OUT);
    dm9000_reg_write(DM9000_GPR, 0);	
    
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

void dm9000_init()
{
    u32 i;
    
    /*设置片选*/
    cs_init();
    
    /*中断初始化*/
    int_init();
    
    /*复位设备*/
    dm9000_reset();
    
    /*捕获dm9000*/
    dm9000_probe();
    
    /*MAC初始化*/
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
	
    /*填充MAC地址*/
    for (i = 0; i < 6; i++)
        dm9000_reg_write(DM9000_PAR+i, mac_addr[i]);
    
    /*激活DM9000*/
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

#define PTK_MAX_LEN 1522

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

void int_issue()
{
    packet_len = dm9000_rx(buffer);	
    
    arp_process();
    
    SRCPND = (1<<4);
    INTPND = (1<<4);
    EINTPEND |= 1<<7; 
}

void dm9000_arp()
{
    while(1)
        arp_request();	
}