OBJS := start.o main.o dev/dev.o lib/lib.o 

CFLAGS := -fno-builtin -I$(shell pwd)/include
export CFLAGS

gboot.bin : gboot.elf
	arm-linux-objcopy -O binary gboot.elf gboot.bin

gboot.elf : $(OBJS)	
	arm-linux-ld -Tgboot.lds -o gboot.elf $^
	
%.o : %.S
	arm-linux-gcc -g -c $^
	
%.o : %.c
	arm-linux-gcc $(CFLAGS) -c $^

lib/lib.o : 
	make -C lib all

dev/dev.o :
	make -C dev all
	
.PHONY: clean
clean:
	make -C lib clean
	make -C dev clean
	rm -f *.o *.elf *.bin *.bak


