all:start.o mem.o  main.o #if want to add rely on files,add "xxx.o"
	arm-linux-ld -Tgboot.lds -o gboot.elf $^
	arm-linux-objcopy -O binary gboot.elf gboot.bin
%.o:%.S
	arm-linux-gcc -g -c $^
%.o:%.c
	arm-linux-gcc -g -c $^	
.PHONY:clean
clean:
	rm *.o *.elf *.bin