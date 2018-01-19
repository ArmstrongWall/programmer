KDIR = /lib/modules/`uname -r`/build
PWD := $(shell pwd)
obj-m := dnw_usb.o
all:
	make -C $(KDIR) M=$(PWD) modules
clean:
	rm -rf *ko *o

