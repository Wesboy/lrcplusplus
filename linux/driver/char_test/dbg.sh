rmmod char_drv.ko
rm /dev/my_drv
insmod char_drv.ko
mknod /dev/my_drv c 100 0
