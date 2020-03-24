CONFIG_MODULE_SIG=n

obj-m := char_driver_demo.o

KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD)

clean:
	rm -rf *.ko *.o *.mod.c *.mod.o *.symvers *.order *.mod *.a
