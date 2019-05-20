#***********************       TIPS         ***********************************
#                    The rules of Makefile
#1.Basic rules	
#targets : prerequisites
#[tab]command       #before  command,add one tab.
#	 e.g			gboot.bin : gboot.elf
#							arm-linux-objcopy -O binary gboot.elf gboot.bin
#
#
#
#2.Using Variables 
#V1 :=V1.o V2.o....  #means V1 behave of V1.o V2.o....
#then use  "$(V1)"  Variables to indicate V1.o V2.o....
#some other system variables:
#															$^  represent of  all   prerequisites
#															$@  represent of  all   targets
#															$<  represent of  first prerequisites
#
#
#3.Phony targets
#e.g:
#.PHONY: clean         #define "clean" to Phony targets 
#clean:
#	rm *.o *.elf *.bin 	 #define  command of "clean"
#
#
#
#4.Gerneral rules
#You can use " %.x " to represent of all file suffix with " .x "
#e.g:
#%.o : %.S
#	arm-linux-gcc -g -c $^
#means from prerequisites(all file suffix with ".s") to generate targets(all file suffix with ".s")
#if there are mem.S,led.S,mmu.S, after excute this instruction,it will generate mem.o,led.o,mmu.o
#
#
#
#

#***********************       TIPS         ************************************


OBJS := start.o main.o dev/dev.o lib/lib.o
#if want to add rely on files,add "xxx.o"

CFLAGS := -fno-builtin -I$(shell pwd)/include
export CFLAGS
#***********************       TIPS         ***********************************
#CFLAGS is used to save Compiler options ,'export' like C language 'extern'
#In C language,some gerneral function such as "printf,strchr,memset" are defined to built-in function(ÄÚ½¨º¯Êý)£¬
#But sometimes you want code it by yourself, maybe have error.
#Sloution is add "-fno-builtin" before compiling.
#***********************       TIPS         ************************************


gboot.bin : gboot.elf
	arm-linux-objcopy -O binary gboot.elf gboot.bin

gboot.elf : $(OBJS)
#$(xxx),xxx is a variables,OBJS is a variables
	arm-linux-ld -Tgboot.lds -o gboot.elf $^

%.o:%.S
	arm-linux-gcc -g -c $^

%.o:%.c
	arm-linux-gcc ${CFLAGS} -c $^
	
lib/lib.o:
	make -C lib all	

dev/dev.o:
	make -C dev all	

.PHONY: clean
clean:
	rm *.o *.elf *.bin 
	make -C lib clean
	make -C dev clean 