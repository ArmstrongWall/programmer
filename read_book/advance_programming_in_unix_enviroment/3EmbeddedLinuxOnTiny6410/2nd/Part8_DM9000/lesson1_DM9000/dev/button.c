#define GPNCON0 (volatile long*)0x7F008830
#define GPLCON1 (volatile long*)0x7F008814

void button_init()
{
		*(GPNCON0) = 0b10;        //set K1(GPN0) to Ext. Interrupt
		*(GPLCON1) = 0b0011<<16;  //set K8(GPL12) to Ext. Interrupt
		
		
	}