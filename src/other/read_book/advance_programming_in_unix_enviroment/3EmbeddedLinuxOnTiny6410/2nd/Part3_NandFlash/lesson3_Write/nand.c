/*
@Platform: Friendly Arm tiny6410
@CPU: S3C6410
@Function: Nand Flash Page read and write 
@Written by Armstrong Wall
@Start wrirte date: 2016.3.8
@Daily: 		2016.3.10  Finish Nand Flash
*/


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
 
 TACLS*7ns         should >0  ns
 (TWRPH0+1)*7ns    should >12 ns
 TWRPH1  				   should >5  ns

 
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
	  //select nandflash chip
	  select_chip();
	  
	  //clear RnB
		clear_RnB();
	
		//send cmd 0x00
		send_cmd(0xff);
		
		//wait RnB to high
		wait_RnB();
		
		//dis_select nandflash chip
		dis_select_chip();

	}


void nand_init()
{
	//nandNFCONF
	//twp--12ns, tcls--12s,tclh--5ns
	*(NFCONF) |= (TACLS<<12) | (TWRPH0<<8) | (TWRPH1<<4);
	*(NFCONT) = (1<<0) | (1<<1);
	
	nand_reset();
	
 }

void NandFlash_PageRead(unsigned long addr,unsigned char* buff)
{
	  int i;

	  //select nandflash chip
		select_chip();
		
		//clear RnB
		clear_RnB();
		
		//send cmd 0x00
		send_cmd(0x00);
		
		//send Column Address twice
		send_addr(0x00);
		send_addr(0x00);
		
		//send Row Address three times
		send_addr(addr&0xff);
		//Low 8 bits
		send_addr((addr<<8)&0xff);
		//Middle 8 bits
		send_addr((addr<<16)&0xff);
		//High 8 bits
		
		//send cmd 0x30
		send_cmd(0x30);
		
		//wait RnB to high
		wait_RnB();
		
		
		//Read data
		for(i=0;i<2048;i++)//A page size is 2K bytes
		{
				buff[i]=*(NFDATA);
			}
		
		
		//dis_select nandflash chip
		dis_select_chip();
		
	}
	
	
void nand_to_ram(unsigned long start_addr,unsigned char* sdram_addr,int size)
{//start_addr is data in nandflash which will copy to ram,set to 0
 //sdram_addr is _start=0x50008000 in memory
 //size is (bss_end  sub _start)= size of (.text + .data + .bss) ,you can see in Linker Script File
	  int i=0;
    for(i=(start_addr <<11);size>0;) //Page address is begin of bit12
//At begining,I code as "for(i=(start_addr <<11);;size>0)",Lack of cycling conditions,
//that means never get out of cycle
	   {
			NandFlash_PageRead(i,sdram_addr);
//Parameter buff is point to 	sdram_addr(0x50008000), so this function
//means copy nandflash(from 0x00000000 of nanflash memory,which load user program)
//to 6410 memory from 0x50008000
			size -= 2048;
			
			sdram_addr +=2048;
			
			i++;
			
	  	}
	  

	}
	
int NandFlash_PageErase(unsigned long addr)
{
	   int ret=0;
	  //select nandflash chip
	  select_chip();
	  
	  //clear RnB
	  clear_RnB();
	  
		//send cmd 0x60
		send_cmd(0x60);
		
		//send Row Address three times
		send_addr(addr&0xff);
		//Low 8 bits
		send_addr((addr<<8)&0xff);
		//Middle 8 bits
		send_addr((addr<<16)&0xff);
		//High 8 bits		
		
		//send cmd 0xD0
		send_cmd(0xD0);
		
		//wait RnB to high
		wait_RnB();
		
		//send cmd 0x70
		send_cmd(0xD0);
		
		//read I/O0,=0 Successful Erase,=1 Error in Erase
		ret = *(NFDATA);
		
		//dis_select nandflash chip
	  dis_select_chip();
	  
	  return ret;
		
	}
	
int  NandFlash_PageWrite(unsigned long addr,unsigned char* buff)
{
	
	  int i=0,ret=0;
	  //select nandflash chip
	  select_chip();
	  
	  //clear RnB
	  clear_RnB();
	  
		//send cmd 0x80
		send_cmd(0x80);
		
		//send Column Address twice
		send_addr(0x00);
		send_addr(0x00);
		
		//send Row Address three times
		send_addr(addr&0xff);
		//Low 8 bits
		send_addr((addr<<8)&0xff);
		//Middle 8 bits
		send_addr((addr<<16)&0xff);
		//High 8 bits
		
		//write data
		for(i=0;i<2048;i++)
		{
			*(NFDATA)=buff[i];
			}
		
		//send cmd 0x10
		send_cmd(0x10);
		
		//wait RnB to high  
		wait_RnB();
		
		//send cmd 0x70
		send_cmd(0x70);
		
		//read I/O0,=0 Successful Program,=1 Error in Program
	  ret = *(NFDATA);
	
	  //dis_select nandflash chip
	  dis_select_chip();
	  
	  return ret;
	}