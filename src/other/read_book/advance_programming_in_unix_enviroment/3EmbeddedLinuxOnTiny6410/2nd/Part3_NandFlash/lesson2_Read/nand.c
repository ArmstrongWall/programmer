#define NFCONT (volatile unsigned long*) 0x70200004
//NAND Flash control register
#define NFSTAT (volatile unsigned long*) 0x70200028
//NAND Flash operation status register
#define NFCMMD (volatile unsigned long*) 0x70200008
//NAND Flash command set register
#define NFADDR (volatile unsigned long*) 0x7020000C
//NAND Flash address set register
#define NFDATA (volatile unsigned char*) 0x70200010 
//NAND Flash data register,the define must be "char",datasheet has an error  
#define NFCONF (volatile unsigned long*) 0x70200000
//NAND Flash Configuration register
/*
 NAND Flash Configuration register has some value which should be calculate
 According to datasheet:
 HCLK			 =133Mhz   
 so Frequency =7ns
 
 TACLS*7ns         should >0ns
 (TWRPH0+1)*7ns    should >12ns
 TWRPH1  				   should >5ns

 
*/
#define TACLS   1//1
#define TWRPH0	2//2
#define TWRPH1  1//1


#define NFCONT (volatile unsigned long*) 0x70200004
//NAND Flash control register



void select_chip()
{
	*(NFCONT) &= ~(1<<1);
//Reg_nCE0,NAND Flash Memory Xm0CSn2 signal control
//0: Force Xm0CSn2 to low(Enable chip select)
	}
	
void dis_select_chip()
{
	*(NFCONT) |= (1<<1);
//Reg_nCE0,NAND Flash Memory Xm0CSn2 signal control
//1: Force Xm0CSn2 to High(Disable chip select)

	}
	
void clear_RnB()
{
	*(NFSTAT) |= (1<<4);
//When RnB low to high transition is occurred, this value set and
//issue interrupt if enabled. To clear this write '1'
	
	}

void send_cmd(unsigned char cmd)
{
		*(NFCMMD) = cmd;
	}	
	

void send_addr(unsigned long addr)
{
		*(NFADDR) = addr;
	}	
	
void wait_RnB()
{
		while(!(*(NFSTAT)& 0x10))
//wait untill bit5(RnB_TransDetect) of NFSTAT to set 1;
//which means RnB from 0(busy) to 1(ready)
		{
			;
			}
	}	

void nand_reset()
{
	  //选中Flash
	  select_chip();
	  
	  //清除RnB信号,以便于检查
		clear_RnB();
	
		//发送0xff命令
		send_cmd(0xff);
		
		//等待RnB
		wait_RnB();
		
		//取消选中nandflash芯片
		dis_select_chip();

	}


void nand_init()
{
	//初始化NFCONF
	//twp--12ns, tcls--12s,tclh--5ns
	//初始化
	*(NFCONF) |= (TACLS<<12) | (TWRPH0<<8) | (TWRPH1<<4);
	*(NFCONT) = (1<<0) | (1<<1);
	
	nand_reset();
	
 }

void NandFlash_PageRead(unsigned long addr,unsigned char* buff)
{
	  int i;
   //这里的顺序都是参考数据手册的
	  //选中nandflash芯片，任何操作都需要这一步
		select_chip();
		
		//清除RnB信号,以便于检查
		clear_RnB();
		
		//发送，命令0x00
		send_cmd(0x00);
		
		//发送列地址
		send_addr(0x00);
		send_addr(0x00);
		
		//发送行地址,因为总线宽度只有8位，所以要每次只能发送8位，发送三次
		send_addr(addr&0xff);
		send_addr((addr<<8)&0xff);
		send_addr((addr<<16)&0xff);
		
		//发送命令0x30
		send_cmd(0x30);
		
		//等待RB信号
		wait_RnB();
		
		
		//读取数据
		for(i=0;i<2048;i++)//一页是2K bytes
		{
				buff[i]=*(NFDATA);
			}
		
		
		//取消选中nandflash芯片
		dis_select_chip();
		
	}
	
	
void nand_to_ram(unsigned long start_addr,unsigned char* sdram_addr,int size)
{
	  int i=0;
    for(i=(start_addr <<11);size>0;) //从第12位开始才是页地址
//At begining,I code as "for(i=(start_addr <<11);;size>0)",Lack of cycling conditions,
//that means never get out of cycle
	   {
			NandFlash_PageRead(i,sdram_addr);
			
			size -= 2048;
			
			sdram_addr +=2048;
			
			i++;
			
	  	}
	  

	}