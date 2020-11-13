#define GPBCON (volatile unsigned long*)0x56000010
#define GPBDAT (volatile unsigned long*)0x56000014

#define	GPB5_out	(1<<(5*2))
#define	GPB6_out	(1<<(6*2))
#define	GPB7_out	(1<<(7*2))
#define	GPB8_out	(1<<(8*2))

void led_init()
{   
    *(GPBCON) = GPB5_out | GPB6_out | GPB7_out | GPB8_out;
}

void led_off()
{
    *(GPBDAT) = 0x7ff;
}

void led_on()
{
    *(GPBDAT) = 0x61f;
}
