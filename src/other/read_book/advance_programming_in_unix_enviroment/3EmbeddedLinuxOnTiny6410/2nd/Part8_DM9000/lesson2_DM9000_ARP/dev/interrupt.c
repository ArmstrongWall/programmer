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
		
#define EINT0MASK  					 *((volatile long*)0x7F008920)     /*中断屏蔽寄存器*/

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
		//DM9000引脚的GPIO配置
		GPNCON |= GPNCON &(~(0x3<<14));//先清零
	    GPNCON |= GPNCON |(0b10<<14);
		//DM9000中断触发方式设置
	  EINT0CON0 |= EINT0CON0 | (0b010<<12);   //Falling edge triggered
		
		/*修改中断屏蔽寄存器EINT0MASK*/
		EINT0MASK = 0;//全部中断都不屏蔽
		
		/*使能中断向量控制寄存器EINT0MASK*/
		VIC0INTENABLE |= 0x3;
		VIC1INTENABLE |= 0x0f;
	
		
		/*DM9000将中断服务函数的地址传送到中断向量地址寄存器VECTADDR中*/
	  DM9000VIC0VECTADDR = (int)DM9000_isr;
		
		/*打开总中断的控制*/
		__asm__(
						//6410也支持非向量中断模式，所以设置相关的cp15寄存器的第24位，把这个功能打开
						"mrc p15,0,r0,c1,c0,0\n"
						"orr r0,r0,#(1<<24)\n"
						"mcr p15,0,r0,c1,c0,0\n"
						
						//开总中断,由于在start.S中把中断给关闭了，所以这里要重新开启
						"mrs r0,cpsr\n"			//先读
						"bic r0,r0,#0x80\n" //再置位，cpsr的bit7 是控制irq disable的
						"msr cpsr_c,r0\n"		//最后写入，只写control域cpsr_c
						:
						:
		);
	
	
	}

int i=0;
//?????????????应该加入中断入口地址
void DM9000_isr()
{
	
	
    //1.保存环境
		__asm__(
				"sub lr,lr,#4\n" 
				"stmfd sp!,{r0-r12,lr}\n"
				//lr(Link Register)子程序链接寄存器，该寄存器值为当前指令地址值加8个字节，
				 //在此减去4个字节，lr就指向了当前指令地址的下一个地址，即中断执行后的下一条指令
				:
				:
					);

					
//2.中断处理   

 
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
	    //3.清除中断
		EINT0PEND   = ~0x0;//set 1 to clear
		


   //4.恢复环境
  __asm__(

				"ldmfd sp!,{r0-r12,pc}^\n"
				//类比stmfd指令，ldmfd的意思就是批量将sp栈中的值恢复r0到r12寄存器中
				//注意，此时后面不是lr了，应该是pc，因为要将刚才保存的下一条指令的地址存到PC指针中，以便程序正常执行
        //^表示把spsr恢复到cpsr

				:
				:
					);
					
	
	    
    
}
