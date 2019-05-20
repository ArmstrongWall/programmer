#define GPKCON0 0x7f008800	//The Memory address of GPK Control Register
#define GPKDAT  0x7f008808  //The Memory address of GPK Data  Register

int gboot_main()
{
	__asm__(
					"ldr r1, =0x11110000\n"
					"str r1, [%0]\n"						  //set GPK4,5,6,7 to output
					"ldr r1, = 0xa0\n"
					"str r1, [%1]\n"						 //set pin state of GPK4,5,6,7
					:
					:"r"(GPKCON0),"r"(GPKDAT)
					:"r1"
	);
	
	
	
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