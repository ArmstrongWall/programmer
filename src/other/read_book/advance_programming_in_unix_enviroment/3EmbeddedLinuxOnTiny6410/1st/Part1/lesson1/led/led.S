.text
.globl _start
#define VIC0_INT	0x71200000
#define VIC1_INT	0x71300000

_start: bl reset
		ldr	pc, _undefined_instruction
		ldr	pc, _software_interrupt
		ldr	pc, _prefetch_abort
		ldr	pc, _data_abort
		ldr	pc, _not_used
		ldr	pc, _irq
		ldr	pc, _fiq
_undefined_instruction:b .
_software_interrupt:b .
_prefetch_abort:b .
_data_abort:b .
_not_used:b .
_irq:b .
_fiq:b .
reset:
		mrs	r0,cpsr
		bic	r0,r0,#0x1f
		orr	r0,r0,#0xd3
		msr	cpsr,r0

		bl set_peri_port
		bl disable_watchdog
		bl disable_irq
		bl init_led
		bl light_led

halt:
		bl halt

set_peri_port:
@告诉cpu外设的地址
	    ldr r0, =0x70000000
	    orr r0, r0, #0x13
	    mcr p15,0,r0,c15,c2,4
		mov	pc, lr

disable_watchdog:
@关闭看门狗
		ldr r0, =0x7E004000
		mov r1, #0
		str r1, [r0] @ str, store,
		mov	pc, lr

disable_irq:
@屏蔽中断
		ldr	r1, =0x0
		ldr	r0, =VIC0_INT
		str	r1, [r0]

		ldr	r1, =0x0
		ldr	r0, =VIC1_INT
		str	r1, [r0]
		mov	pc, lr

init_led:
@设置GPK为输出模式
		ldr r1, =0x7F008800
		ldr r0, =0x11110000
		str r0, [r1]					@向GPKCON 0x7F008800地址写0x11110000
		mov	pc, lr

light_led:
@点亮LED1
		ldr r1, =0x7F008808
		ldr r0, =0x0					@向GPKDAT 0x7F008808地址写0x0
		str r0, [r1]

