.text
.global _start
_start:
@协处理器cp15访问指令
	mrc p15,0,r0,c0,c0,0
	@读取cp15的main ID寄存器的值，可以获得芯片架构型号

@ldr存储器访问指令
	mov r0,#0xff
	ldr r1,=0x50009000
	@这句话相当于mov r1,#0x50009000(这句是无法实现的)
	@也可以通过直接在调试过程中修改寄存器值完成
	str r0,[r1]
	ldr r2,[r1]

@str存储器访问指令
	mov r0,#0xff
	str r0,[r1]


@程序状态字寄存器访问指令
	mrs r0,cpsr
	orr r0,#0b100
	msr cpsr,r0

@ror移位指令范例
	mov r1,#0b11
	mov r1,r1,ror#1

@lsl移位指令范例
	mov r1,#0b1
	mov r1,r1,lsl#2

@bl跳转指令范例
	mov r1,#5
	mov r2,#6
	cmp r1,r2
	bl  fun1@用b跳转指令就会使得程序跑飞

	mov r2,#6

	fun1:
	mov r1,#2
	mov r2,#3
	mov pc,lr

@b跳转指令范例
	mov r1,#5
	mov r2,#6
	cmp r1,r2
	bgt branch1
	add r3,r1,r2
	b	end

	branch1:
	sub r3,r1,r2
	end:
	nop

@tst比较指令范例
	mov r1,#0b101
	tst r1,#0b001

	mov r1,#0b0
	tst r1,#0b0

	mov r1,#0b101
	tst r1,#0b100

@cmp比较指令范例
	mov r1,#2
	cmp r1,#1

	mov r1,#2
	cmp r1,#3

	mov r1,#2
	cmp r1,#2



@bic指令范例
	mov r0,#0b1101
	bic r0,r0,#0b1011

@and指令范例
	mov r1,#5
	and r2,r1,#0
	mov r1,#5
	and r2,r1,#1
@add指令范例
	mov r2,#4
	add r1,r2,#2 @操作数1不能是立即数
@sub指令范例
	mov r2,#4
	sub r1,r2,#2 @操作数1不能是立即数

	mov r0,#1
	sub r3,r1,r0

@mvn指令范例
	mvn r1,#0b10
	mvn r2,#5
	mvn r3,r1
@mov指令范例
	mov r1,#8
	mov r2,r1
	mov r3,#10

