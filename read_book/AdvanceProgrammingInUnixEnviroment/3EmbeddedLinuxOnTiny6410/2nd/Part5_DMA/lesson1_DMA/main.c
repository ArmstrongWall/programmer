/*
@Platform: Friendly Arm tiny6410
@CPU: S3C6410
@Function: Bootloader0 ,init cpu 
@Written by Armstrong Wall
@Start wrirte date: 2016.3.3
@Daily: 		2016.3.6  Finish init MMU
 						2016.3.7  Finish interrupt
 						2016.3.10 Nand Flash 
            2016.3.14 Uart 	
            2016.3.14 DMA 	
            
            
            					
*/
char *buf = "Hello world";

int gboot_main()
{
	
	unsigned long a=2000000;
	int num;
//A page dataof Nand Flash 
#ifdef MMU_ON	
  mmu_init();
#endif

  led_init();
	
	button_init();
	init_irq();
	uart_init();
	
	led_off();
	while(a--);
	led_on();

  dma_init(); 
	dma_start();
	
	lcd_init();
		
	while(1)
	{
  	  printf("\n*******************************\n\r");
  	  printf("\n*******************************\n\r");
  	  printf("1:Download Linux Kernel from TFTP\n\r");
  	  printf("2:Boot Linux from RAM\n\r");
  	  printf("3:Boot Linux from Nand Flash\n\r");
  	  printf("\n Please Select\n\r");
  	  
  	  scanf("%d",&num);
  	  
  	  switch(num)
  	  {
					case 1:
						//tftp_load();
						printf("you Select 1\n\r");
						break;
					case 2:
						//boot_linux_ram();
						printf("you Select 2\n\r");
					  break;
					case 3:
						//boot_linux_nand();
						printf("you Select 3\n\r");
					  break;
					  
					default:
						printf("Error: wrong selection!\n\r");
						break;
						

  	  	}
  	  
  	  
  	  
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
