#include"vsprintf.h"

unsigned char outbuf[1024];
unsigned char inbuf[1024];

int printf(const char* fmt, ...)
//Variadic input  �ɱ����
{
	  int i;
	  va_list args;
//����б�
//1.change Variadic to char
		va_start(args,fmt);
		
		vsprintf((char*)outbuf,fmt,args);
		
		va_end();
//��fmtת�����ַ���		

//2.print char to UART
		for(i=0;i<strlen((char*)outbuf);i++)
		{
				put_char(outbuf[i]);
		}

		return i;
	}


int scanf(const char* fmt, ...)
{
	unsigned char c;
	int i =0;
/*****************************************
				Here is An big error commited. 

if you write "int i;",you can not get right scanf,
Beacuse, ref to below Row 56  "inbuf[i++] = c ;"
you may pass inbuf[a random num]=c,so you can not success.
Maybe you can use clear BSS to correct this mistake,
But more important is init every variable to 0;


*****************************************/
	va_list args;
//1.��ȡ�����ַ���
		while(1)
		{
				c = get_char();
				if((c==0x0d) || (c == 0x0a))
					{
							inbuf[i] = '\n';
							break;
						}
				else
					{
						inbuf[i++] = c ;

						}
			}
		

//2.��ʽת��
		va_start(args,fmt);
		
		vsscanf((char*)inbuf,fmt,args);
		
		va_end(args);
		
	  return i;
	
	}