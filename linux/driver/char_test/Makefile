ifneq ($(KERNELRELEASE),)

obj-m := char_drv.o
else
KERNEL_DIR=/lib/modules/$(shell uname -r)/build
#KERNEL_DIR=/home/cwp/git-work/nanopi-m2/linux-3.4.y
PWD	:= $(shell pwd)

all:
	make -C $(KERNEL_DIR) M=$(PWD) modules

clean:
	make -C $(KERNEL_DIR) M=$(PWD) modules clean
	rm -rf modules.order

endif
