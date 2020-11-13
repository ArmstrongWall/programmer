/*
@Platform: Friendly Arm tiny6410
@CPU: S3C6410
@Function: Bootloader0 ,init cpu 
@Written by Armstrong Wall
@Start wrirte date: 2016.3.7
@Daily: 		2016.3.7  Finish init interrupt
						2016.3.30 add DM9000 interrupt
*/
#include "dm9000.h"
#include "arp.h"

#define EINT0CON0     			 *((volatile long*)0x7F008900)
#define EINT0CON1  	   			 *((volatile long*)0x7F008904)	
		
#define EINT0MASK  					 *((volatile long*)0x7F008920)     /*�ж����μĴ���*/

#define VIC0INTENABLE 			 *((volatile long*)0x71200010)  //VECTORED INTERRUPT CONTROLLERS
#define VIC1INTENABLE 			 *((volatile long*)0x71300010)  //VECTORED INTERRUPT CONTROLLERS

#define EINT0VIC0VECTADDR    *((volatile long*)0x71200100)  //VECTOR ADDRESS REGISGERS
#define EINT20VIC0VECTADDR   *((volatile long*)0x71300104)  //VECTOR ADDRESS REGISGERS

#define EINT0PEND						 *((volatile long*)0x7F008924)  //External Interrupt 0(Group0) Pending Register

#define VIC0ADDRESS					 *((volatile long*)0x71200F00)  //Vector Address Register (VIC0)
#define VIC1ADDRESS					 *((volatile long*)0x71300F00)  //Vector Address Register (VIC1)


#define GPNCON  						 *((volatile long*)0x7F008830)
#define GPLCON1 						 *((volatile long*)0x7F008814)
#define DM9000VIC0VECTADDR   *((volatile unsigned long *)0x71200104) //VECTOR ADDRESS REGISGERS

void DM9000_isr();




void init_irq()
{
		//DM9000���ŵ�GPIO����
		GPNCON |= GPNCON &(~(0x3<<14));//������
	    GPNCON |= GPNCON |(0b10<<14);
		//DM9000�жϴ�����ʽ����
	  EINT0CON0 |= EINT0CON0 | (0b010<<12);   //Falling edge triggered
		
		/*�޸��ж����μĴ���EINT0MASK*/
		EINT0MASK = 0;//ȫ���ж϶�������
		
		/*ʹ���ж��������ƼĴ���EINT0MASK*/
		VIC0INTENABLE |= 0x3;
		VIC1INTENABLE |= 0x0f;
	
		
		/*DM9000���жϷ������ĵ�ַ���͵��ж�������ַ�Ĵ���VECTADDR��*/
	  DM9000VIC0VECTADDR = (int)DM9000_isr;
		
		/*�����жϵĿ���*/
		__asm__(
						//6410Ҳ֧�ַ������ж�ģʽ������������ص�cp15�Ĵ����ĵ�24λ����������ܴ�
						"mrc p15,0,r0,c1,c0,0\n"
						"orr r0,r0,#(1<<24)\n"
						"mcr p15,0,r0,c1,c0,0\n"
						
						//�����ж�,������start.S�а��жϸ��ر��ˣ���������Ҫ���¿���
						"mrs r0,cpsr\n"			//�ȶ�
						"bic r0,r0,#0x80\n" //����λ��cpsr��bit7 �ǿ���irq disable��
						"msr cpsr_c,r0\n"		//���д�룬ֻдcontrol��cpsr_c
						:
						:
		);
	
	
	}

int i=0;
//?????????????Ӧ�ü����ж���ڵ�ַ
void DM9000_isr()
{
	
	
    //1.���滷��
		__asm__(
				"sub lr,lr,#4\n" 
				"stmfd sp!,{r0-r12,lr}\n"
				//lr(Link Register)�ӳ������ӼĴ������üĴ���ֵΪ��ǰָ���ֵַ��8���ֽڣ�
				 //�ڴ˼�ȥ4���ֽڣ�lr��ָ���˵�ǰָ���ַ����һ����ַ�����ж�ִ�к����һ��ָ��
				:
				:
					);

					
//2.�жϴ���   

 
    packet_len = dm9000_rx(buffer);	
  
    arp_process();
   // led_on();
/*    if(i>=0 && i <=100)
        led_on(); 
    else
        led_off();
    i++;
    if(i==200)
        i=0;
*/			  		
	    //3.����ж�
		EINT0PEND   = ~0x0;//set 1 to clear
		


   //4.�ָ�����
  __asm__(

				"ldmfd sp!,{r0-r12,pc}^\n"
				//���stmfdָ�ldmfd����˼����������spջ�е�ֵ�ָ�r0��r12�Ĵ�����
				//ע�⣬��ʱ���治��lr�ˣ�Ӧ����pc����ΪҪ���ղű������һ��ָ��ĵ�ַ�浽PCָ���У��Ա��������ִ��
        //^��ʾ��spsr�ָ���cpsr

				:
				:
					);
					
	
	    
    
}
