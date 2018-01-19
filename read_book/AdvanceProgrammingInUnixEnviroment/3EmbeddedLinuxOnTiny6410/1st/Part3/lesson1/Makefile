all:start.o
	arm-linux-ld -Ttext 0x50000000 -o start.elf $^
%.o:%.S
	arm-linux-gcc -g -o $@ $^ -c
clean:
	rm *.o *.elf
