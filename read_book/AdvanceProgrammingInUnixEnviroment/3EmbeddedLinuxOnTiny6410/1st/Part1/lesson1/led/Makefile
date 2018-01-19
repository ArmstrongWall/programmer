all:  led.o 
	arm-linux-ld -Tled.lds -o led.elf $^
	arm-linux-objcopy -O binary led.elf led.bin
	
%.o : %.S
	@arm-linux-gcc -g -o $@ -c $^
	
.PHONY: clean
clean:
	rm *.o led.elf led.bin


