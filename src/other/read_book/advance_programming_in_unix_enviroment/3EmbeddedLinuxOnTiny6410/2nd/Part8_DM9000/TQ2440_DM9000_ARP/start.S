.text
.global _start
_start:
	b reset
	ldr pc, _undifined_instruction
	ldr pc, _software_interrupt
	ldr pc, _prefetch_abort
	ldr pc, _data_abort
	ldr pc, _not_used
	ldr pc, _irq
	ldr pc, _fiq
	

_undifined_instruction: .word undifined_instruction
_software_interrupt: .word software_interrupt
_prefetch_abort: .word prefetch_abort
_data_abort: .word data_abort
_not_used: .word not_used
_irq: .word irq
_fiq: .word reset

undifined_instruction:
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
	sub lr, lr, #4  
	stmfd sp!, {r0-r12, lr}     /* 保护现场 */  
	bl handle_int               
	ldmfd sp!, {r0-r12, pc}^    /* 恢复现场，^表示把spsr恢复到cpsr */  
	
fiq:	
	nop

reset:
	bl set_svc
	bl disable_watchdog
	bl disable_interrupt
	bl disable_mmu
	bl init_clock
	bl init_sdram
	bl init_stack
	bl nand_init
	bl copy_to_ram
	bl clean_bss
	ldr pc, =gboot_main
@	bl light_led

set_svc:
	mrs r0, cpsr
	bic r0, r0,#0x1f
	orr r0, r0,#0xd3
	msr cpsr, r0
	mov pc, lr

#define pWTCON 0x53000000
disable_watchdog:
	ldr r0, =pWTCON
	mov r1, #0x0
	str r1, [r0]
	mov pc, lr

disable_interrupt:
	mvn r1, #0x0
	ldr r0, =0x4a000008
	str r1, [r0]
	mov pc, lr
	
disable_mmu:
	mcr p15,0,r0,c7,c7,0
	mrc p15,0,r0,c1,c0,0
	bic r0, r0, #0x00000007
	mcr p15,0,r0,c1,c0,0
	mov pc, lr

#define CLKDIVN 0x4c000014
#define MPLLCON 0x4c000004
#define MPLL_405MHZ ((127<<12)|(2<<4)|(1<<0))

init_clock:
	ldr r0, =CLKDIVN
	mov r1, #0x5
	str r1, [r0]
	
	mcr p15,0,r0,c1,c0,0
	orr r0,r0,#0xc0000000
	mcr p15,0,r0,c1,c0,0
	
	ldr r0, =MPLLCON
	ldr r1, =MPLL_405MHZ
	str r1, [r0]
	mov pc, lr
	
#define mem_contrl 0x48000000
init_sdram:
	ldr r0, =mem_contrl 
	add r3, r0, #4*13
	adrl r1, mem_data

0:
	ldr r2, [r1], #4
	str r2, [r0], #4
	cmp r0, r3
	bne 0b
	mov pc, lr
	
copy_to_ram:
	mov r0, #0
	ldr r1, =_start
	ldr r2, =bss_end
	sub r2,r2,r1
	
	mov ip,lr
	bl nand_to_ram
	mov lr, ip
	mov pc,lr
	
init_stack:
	msr cpsr_c, #0xd2
	ldr sp, =0x33000000	@此处实际设置的是r13_irq			
	msr cpsr_c, #0xd3
	ldr sp, =0x34000000	@此处实际设置的是r13_svc
	mov pc, lr

clean_bss:
	ldr r0, =bss_start
	ldr r1, =bss_end
	cmp r0, r1
	moveq pc, lr

clean_loop:
	mov r2, #0
	str r2, [r0], #4
	cmp r0, r1
	bne clean_loop
	mov pc, lr

mem_data:
	.long 0x22000000 
	.long 0x00000700
	.long 0x00000700
	.long 0x00000700
	.long 0x00000700
	.long 0x00000700
	.long 0x00000700
	.long 0x00018001
	.long 0x00018001
	.long 0x008c04f5
	.long 0x000000b1
	.long 0x00000030
	.long 0x00000030

#define GPBCON 0x56000010
#define GPBDAT 0x56000014
light_led:
	ldr r0, =GPBCON
	ldr r1,=0x15400
	str r1, [r0]
	
	ldr r0, =GPBDAT
	ldr r1,=0x6BF
	str r1, [r0]
	mov pc, lr
