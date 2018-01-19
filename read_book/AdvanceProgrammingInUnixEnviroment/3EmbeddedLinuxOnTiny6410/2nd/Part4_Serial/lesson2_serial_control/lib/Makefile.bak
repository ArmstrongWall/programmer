objs := div64.o lib1funcs.o ctype.o muldi3.o printf.o string.o vsprintf.o

all : $(objs)
	arm-linux-ld -r -o lib.o $^
	
%.o : %.c
	arm-linux-gcc ${CFLAGS} -c $^
	
%.o : %.S
	arm-linux-gcc ${CFLAGS} -c $^

clean:
	rm -f *.o		
	
