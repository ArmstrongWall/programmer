/*
@Platform: Friendly Arm tiny6410
@CPU: S3C6410
@Function: Bootloader0 ,init cpu 
@Written by Armstrong Wall
@Start wrirte date: 2016.3.3
@Daily: 		2016.3.6  Finish init MMU
 						2016.3.7  Finish interrupt
 						2016.3.10 Nand Flash 
*/


int gboot_main()
{
	unsigned char buff[2048];
	unsigned long a=5000000;
//A page dataof Nand Flash 
#ifdef MMU_ON	
  mmu_init();
#endif

  led_init();
	
	button_init();
	init_irq();
	
	led_off();
	while(a--);
	
	NandFlash_PageErase(64*5+1);
//before write data to Specified page,you must Erase Specified page

  buff[0] = 100;
  
  NandFlash_PageWrite(64*5+1,buff);
  
  buff[0] = 10;
  
  NandFlash_PageRead(64*5+1,buff);
  
  
  if(buff[0] = 100)
  	{
  		 led_on();
  		}
	
	while(1)
	{

		}
	
	
	return 0;
}

/*
int gboot_main()
{
	unsigned long a=500000;
	*(GPKCON0) = 0x11110000;
	
	while(1)
	{
		light_led();
		
	  *(GPKDAT)  = 0xb0;
	  while(a--);
	  a=500000;
	  
	  
	  *(GPKDAT)  = 0x70;
	  while(a--);
	  a=500000;
	  
	  *(GPKDAT)  = 0xd0;
	  while(a--);
	  a=500000;
	  
	  *(GPKDAT)  = 0xe0;
	  while(a--);
	  a=500000;
	  
	  
		
		}
	
	
	
	return 0;
}
*/