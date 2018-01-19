objs := mem.o  mmu.o  nand.o uart.o led.o dma.o   dm9000.o arp.o interrupt.o button.o #bmp.o lcd.o 

all : $(objs)
	arm-linux-ld -r -o dev.o $^
	
%.o : %.c
	arm-linux-gcc ${CFLAGS} -c $^
	
%.o : %.S
	arm-linux-gcc ${CFLAGS} -c $^

.PHONY: clean
clean:
	rm -f *.o *.bak	
	
