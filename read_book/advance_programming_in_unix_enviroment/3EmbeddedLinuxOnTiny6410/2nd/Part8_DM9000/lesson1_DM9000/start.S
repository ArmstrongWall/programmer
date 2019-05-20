@Platform: Friendly Arm tiny6410
@CPU: S3C6410
@Function: Bootloader0 ,init cpu 
@Written by Armstrong Wall
@Start wrirte date: 2016.1.20
@Daily: 2016.2.26 Finish init_clock:
@       2016.3.2  Finish init DDR Memory
@
@Attention: Comment is under code.
@          
@
@
@
@
@

.text
.global _start
_start:

@set Exception processing modes,total has 7 Exception type:
@Exception type:          Mode:            Normal address:
@Reset:	                  Supervisor:	   0x00000000
@Undefined instructions:  Undefined:       0x00000004
@Software interrupt:	  Supervisor:	   0x00000008
@Prefetch Abort:	  Abort:           0x0000000c
@Data Abort:              Abort:           0x00000010
@IRQ (interrupt):	  IRQ:             0x00000018(jump to 10,lose 14)
@FIQ (fast interrupt):    FIQ:             0x0000001c

	b reset														
@jump to CPU Power-on init,include many ... see below
	ldr pc, _undefine_instruction			
	ldr pc, _software_interrupt
	ldr pc, _prefetch_abort
	ldr pc, _data_abort
	ldr pc, _not_used								  
@because Normal address jump to 10,lose 14, for aline 4 bytes,need to add a word named "_not_used"
	ldr pc, _irq
	ldr pc, _fiq
	

_undefine_instruction: .word undefine_instruction  @define a word type of data,a word=4 bytes
_software_interrupt: .word software_interrupt
_prefetch_abort: .word prefetch_abort
_data_abort: .word data_abort
_not_used: .word not_used
_irq: .word irq
_fiq: .word fiq


undefine_instruction:							
@define the Exception of "undefine_instruction" to do
	nop

software_interrupt:
	nop

prefetch_abort:
	nop

data_abort:
	nop

not_used:
	nop

irq:
	nop

fiq:
	nop

reset:										  
@define the Exception of "reset" to do
	bl set_svc 
	bl set_peri_port
	bl disable_watchdog
	bl disable_interrupt
	bl disable_mmu
	bl init_clock						  
@set clock div ratio
	bl mem_init      				  
@init memory(DDR)
	bl init_stack
@after init stack,we can call C function
	bl nand_init 							
@init nandflash
	bl copy_to_ram
	bl clear_bss
	ldr pc, =gboot_main
@	bl light_led


set_svc:
@bootloader,keneral...should work in svc mode
	mrs r0, cpsr
	bic r0, r0,#0x1f   
	orr r0, r0,#0xd3
	msr cpsr, r0
	mov pc, lr

set_peri_port:
	ldr r0, =0x70000000				
@set base address of Peripheral Port Memory Remap Register
	orr r0, r0 ,#0x13  				
@set size value of Peripheral Port Memory Remap Register
	mcr p15,0,r0,c15,c2,4 		
@write  Peripheral Port Memory Remap Register
	mov pc,lr
	
#define pWTCON 0x7e004000 	
@The Memory address of WTCON 
disable_watchdog:
	ldr r0, =pWTCON
	mov r1, #0x0							
@use "mvn" is convenient to get !0x0
	str r1, [r0]							
@write value of r1(!0x0) to Memory address which r0 point to(WTCON)
	mov pc, lr

disable_interrupt:
	mvn r1, #0x0
	ldr r0, =0x71200014				
@The Memory address of VIC0INTENCLEAR Register
	str r1, [r0]							
@disable interrupt
	
	ldr r0, =0x71300014				
@The Memory address of VIC1INTENCLEAR Register
	str r1, [r0]							
@disable interrupt
	mov pc, lr
	
disable_mmu:
	mcr p15,0,r0,c7,c7,0 			
@invalidate ICache and DCache
	mrc p15,0,r0,c1,c0,0 			
@read control reg
	bic r0, r0 , #0x00000007  
	mcr p15,0,r0,c1,c0,0			
@write to disable mmu and I/DCache
	mov pc, lr

#define OTHERS   0x7e00f900 @The Memory address of OTHERS Register which control SYNC Mode
#define CLK_DIV0 0x7e00f020 @The Memory address of Clock  divider control  Register
#define DIV_VAL  ((0x0<<0)|(0x1<<9)|(0x1<<8)|(0x3<<12))		@Assignment value by left cyclic shift(<<)
@Value written into reg
@RATIO type 			Correspond Bit    set value
@PCLK_RATIO		           [15:12]            3
@HCLKX2_RATIO			   [11:9]             1
@HCLK_RATIO			   [8]                1
@ARM_RATIO                         [3:0]              0 

#define MPLL_CON  0x7E00F010 @The Memory address of MPLL_CON Register
#define APLL_CON  0x7E00F00C @The Memory address of APLL_CON Register

#define PLL_VAL   ((1<<31)|(266<<16)|(3<<8)|(1<<0))	@Value written into PLL control reg
@MDIV=266,PDIV=3,SDIV=1,Target FOUT =533MHz (FIN=12MHz)

#define CLK_SRC  0x7E00F01C @The Memory address of CLK_SRC Register

@ARMCLK =APLLout/(DIVARM+1)=533Mhz;
@HCLKx2 =MPLLout/(DIVhclkx2+1)=266;
@HCLK   =HCLKx2 /(DIVhclk+1)=133Mhz ;
@CLK    =HCLKx2 /(DIVpclk+1)=66Mhz ;


init_clock:
	ldr r0, =CLK_DIV0
	ldr r1, =DIV_VAL
	str r1, [r0]							
@write  clock div ratio into Clock  divider control  Register
	
	ldr r0, =OTHERS
	ldr r1, [r0]							
@read OTHERS Register value to r1
	bic r1,r1,#0x80						
@write SYNCMODE bit to 1,write SYNCMUX bit to 0(use MPLL)
	
	ldr r0, =APLL_CON
	ldr r1, =PLL_VAL
	str r1,[r0]								
@set APLL=533MHz
	
	ldr r0, =MPLL_CON
	ldr r1, =PLL_VAL
	str r1,[r0]								
@set MPLL=533MHz	
	
	ldr r0, =CLK_SRC
	mov r1, #0x3
	str r1,[r0]								
@set MPLL=533MHz	Control MUXMPLL
	
	mov pc, lr
	
copy_to_ram:
@Accroding to ATPCS(ARM-Thumb Procedure Call Standard)
@ATPCS tells function parameters is recommended no more than 4, 
@if the number of parameters is less than or equal to 4, 
@then by the parameter R0, R1, R2, R3 four registers are passed; 
@if the number is greater than 4 parameters, 
@greater than 4 section must pass through the stack.

	mov r0, #0							  
@r0,parameters: start_addr, copy from 0 address of nand flash
	ldr r1, =_start           
@r1,parameters: sdram_addr is _start=0x50008000
	ldr r2, =bss_end
	sub r2, r2, r1						
@r2,parameters: size is _start sub bss_end
  
  mov ip, lr
	bl  nand_to_ram;
	mov lr, ip
	
	mov pc, lr
	
copy_loop:
	ldr r2, [r0], #4					
@read Stepping Stone to r2,add by 4 word
	str r2, [r1], #4				  
@write value of r2 to r1
	cmp r0, r3
	bne copy_loop
	
	mov pc, lr
	
init_stack:
	msr cpsr_c,0xd2
@enter 	Mode  IRQ
	ldr sp, =0x53000000
@init R13_irq reg,set interrupt stack				 


@****************Introduction to msr***********************
@MSR - Load specified fields of the CPSR or SPSR with an immediate constant, 
@or from the contents of a general-purpose register.
@Syntax:
@MSR{cond} <psr>_<fields>, #immed_8r 
@MSR{cond} <psr>_<fields>, Rm where: cond is an optional condition code. 
@<psr> is either CPSR or SPSR.  
@<fields> specifies the field or fields to be moved.<fields> can be one or more of:
@					c control field mask byte (PSR[7:0])
@					x extension field mask byte (PSR[15:8])
@					s status field mask byte (PSR[23:16)
@					f flags field mask byte (PSR[31:24]).
@immed_8r is an expression evaluating to a numeric constant.
@The constant must correspond to an 8-bit pattern rotated by an even number of bits within a 32-bit word. 
@Rm is the source register.
@************************************************************
	
	msr cpsr_c,0xd3				   
@enter 	Mode  Supervisor
	ldr sp, =0x54000000			 
@init R13_svc reg,set svc stack, 0x50000000+64MB
	mov pc, lr
	
clear_bss:
	ldr r0, =bss_start			 
@record bss start address
	ldr r1, =bss_end				 
@record bss end address
	
	cmp r0, r1
	moveq pc, lr				     
@if start=end,return
	
clear_bss_loop:
	mov r2, #0
	str r2, [r0],#4					 
@clear now address to #0,then add a word,for next address clear
	cmp r0, r1
	bne clear_bss_loop
	mov pc, lr
		
	#define GPKCON0 0x7f008800	
@The Memory address of GPK Control Register
	#define GPKDAT  0x7f008808  
@The Memory address of GPK Data  Register

.global light_led					  
@Declared light_led as global variables
light_led:
	ldr r0, = GPKCON0
	ldr r1, =0x11110000
	str r1, [r0]							
@set GPK4,5,6,7 to output
	
	ldr r0, = GPKDAT
	ldr r1, = 0x50
	str r1, [r0]							
@set pin state of GPK4,5,6,7

	ldr r0, =0x1fffff
  
water_light:
  	sub r0,r0,#0x1
	cmp r0,#0x0
	bne water_light

	
	ldr r0, = GPKDAT
	ldr r1, = 0xa0
	str r1, [r0]							
@set pin state of GPK4,5,6,7
















