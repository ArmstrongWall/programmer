objs := mem.o button.o mmu.o interrupt.o nand.o uart.o led.o

all : $(objs)
	arm-linux-ld -r -o dev.o $^
	
%.o : %.c
	arm-linux-gcc ${CFLAGS} -c $^
	
%.o : %.S
	arm-linux-gcc ${CFLAGS} -c $^

.PHONY: clean
clean:
	rm -f *.o		
	
