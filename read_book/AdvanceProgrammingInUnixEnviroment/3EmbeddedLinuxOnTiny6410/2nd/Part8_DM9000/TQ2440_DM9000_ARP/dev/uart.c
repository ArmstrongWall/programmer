#define GPHCON (*(volatile unsigned long*)0x56000070)
#define ULCON0 (*(volatile unsigned long*)0x50000000)
#define UCON0  (*(volatile unsigned long*)0x50000004)
#define UBRDIV0  (*(volatile unsigned long*)0x50000028)
#define UTRSTAT0 (*(volatile unsigned long*)0x50000010)
#define UTXH0 (*(volatile unsigned long*)0x50000020)
#define URXH0 (*(volatile unsigned long*)0x50000024)

#define PCLK 50000000
#define BAUD 115200

void uart_init()
{
    //1.配置引脚功能
    GPHCON &= ~(0xf<<4);
    GPHCON |= (0xa<<4);
    
    //2.1 设置数据格式
    ULCON0 = 0b11;
    
    //2.2 设置工作模式
    UCON0 = 0b1001; 
    
    //3. 设置波特率	
    UBRDIV0 =(int)(PCLK/(BAUD*16)-1);
}


void putc(unsigned char ch)
{
    while (!(UTRSTAT0 & (1<<2)));
	UTXH0 = ch;  
}


unsigned char getc(void)
{
    unsigned char ret;

	while (!(UTRSTAT0 & (1<<0)));
	// 取数据
	ret = URXH0;  
	
	if ( (ret == 0x0d) || (ret == 0x0a) )
	{
	    putc(0x0d);
	    putc(0x0a);	
	}      	
	else
	    putc(ret);
	    
        return ret;
}


void uart_send_string(char *str)
{
    while(*str)
    {
        putc(*str++);	
    }	
    putc(0x0d);
    putc(0x0a);
	
}

