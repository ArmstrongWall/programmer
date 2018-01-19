#define GPFCON  (volatile unsigned long *)0x56000050

/*
 * K1,K2,K3,K4∂‘”¶GPF1°¢GPF4°¢GPF2°¢GPF0
 */
#define GPF0_int     (0x2<<(0*2))
#define GPF1_int     (0x2<<(1*2))
#define GPF2_int     (0x2<<(2*2))
#define GPF4_int     (0x2<<(4*2))

#define GPF0_msk    (3<<(0*2))
#define GPF1_msk    (3<<(1*2))
#define GPF2_msk    (3<<(2*2))
#define GPF4_msk    (3<<(4*2))

void button_init()
{   
    	*(GPFCON) &= ~(GPF0_msk | GPF1_msk | GPF2_msk | GPF4_msk);
	*(GPFCON) |= GPF0_int | GPF1_int | GPF2_int | GPF4_int;
}