@[TOC](ubuntu18.04下动态加载一个字符设备驱动)

# 1、字符设备驱动编写
首先字符设备驱动注册需要使用到
int register_chrdev(unsigned int major, const char *name, struct file_operations *fops);

这里还有file_operations的操作接口定义(删减了暂时不需要了解的接口定义)
```javascript
struct file_operations {
	struct module *owner;
	ssize_t (*read) (struct file *, char __user *, size_t, loff_t *);
	ssize_t (*write) (struct file *, const char __user *, size_t, loff_t *);
	int (*open) (struct inode *, struct file *);
} __randomize_layout;
```
```javascript
#include <linux/cdev.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h>

static int my_drv_open(struct inode *inode, struct file *fl);

static struct file_operations my_drv_fops={
    .open = my_drv_open,
};

static int my_drv_open(struct inode *inode, struct file *fl)
{
    int major_id;
    
    //字符设备注册
    printk("my_drv_open\r\n");

    return 0;
}

int my_drv_init(void)
{
    register_chrdev(100, "my_drv", &my_drv_fops);
    return 0;
    
}

void my_drv_exit(void)
{
    unregister_chrdev(100, "my_drv");
}

module_init(my_drv_init);
module_exit(my_drv_exit);
MODULE_AUTHOR("cwp");
MODULE_LICENSE("GPL");
```
# 2、Makefile编写
这里因为我的测试环境是选择直接在ubuntu下的所有Kernel路径选择/lib/modules
```javascript
KERNEL_DIR=/lib/modules/$(shell uname -r)/build
PWD	:= $(shell pwd)

all:
	make -C $(KERNEL_DIR) M=$(PWD) modules

clean:
	make -C $(KERNEL_DIR) M=$(PWD) modules clean
	rm -rf modules.order

obj-m += char_drv.o
```

如果是要选择在其他目标测试平台上，可以把KERNEL_DIR修改为你对应的kernel路径就可以了，类似
```javascript
KERNEL_DIR=/home/cwp/git-work/nanopi-m2/linux-3.4.y
```

注意内核源码要配置好，且编译过。
# 3、动态加载设备
非root用户下操作所以需要sudo
sudo insmod char_drv.ko
cat /proc/devices 
![在这里插入图片描述](https://img-blog.csdnimg.cn/2019061923503979.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2E5MzUzNjcyNzY=,size_16,color_FFFFFF,t_70)
可以看到/proc/devices已经有设备，主设备号为100

接着我需要在dev里创建设备
sudo mknod /dev/my_drv c 100 0
![在这里插入图片描述](https://img-blog.csdnimg.cn/20190620000153146.png)
# 4、简单测试
写一个简单的测试应用

```javascript
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    if(open("/dev/my_drv",O_RDWR) < 0)
        printf("/dev/my_drv can't open!\r\n");

    return 0;
}
```
编译后运行
正常是看不到printk打印信息的，只有sudo dmesg后可以看到（PS：后续打印信息修改可以用grep查找 命令：sudo dmesg | grep my_drv）
![在这里插入图片描述](https://img-blog.csdnimg.cn/20190620000505327.png)


# 5、增加读写测试
对一个整型buf进行读写
驱动部分的修改
新增加头文件
read时，需要使用copy_to_user，用于驱动从内核空间把数据拷贝到用户空间
write时，需要使用到copy_from_user，用于驱动从用户空间拷贝数据到内核空间

```javascript
#include <linux/uaccess.h>
#include <linux/errno.h>
	
	......
	......
	
static ssize_t my_read(struct file *rfl, char __user *rbuf, size_t count, loff_t *lf)
{

    printk("read buf\r\n");

    unsigned int buf_len = (unsigned int)(sizeof(val)/sizeof(int));
    int i;

    if(buf_len > count)
        buf_len = count;
        
    if(copy_to_user(rbuf, val, buf_len))
    {
        return -EFAULT;
    }


    for(i = 0; i < buf_len;i++)
        printk("char_drv read val[%d]=%d\r\n", i, val[i]);

    
    return 0;
}

static ssize_t my_write(struct file *wfl, const char __user *wbuf, size_t count, loff_t *lf)
{
    printk("write buf\r\n");

    unsigned int buf_len = sizeof(val)/sizeof(int);
    int i;

    if(buf_len > count)
        buf_len = count;
    if(copy_from_user(val, wbuf, buf_len))
    {
        return -EFAULT;
    }
    
    for(i = 0; i < buf_len;i++)
        printk("char_drv write val[%d]=%d\r\n", i, val[i]);

    return 0;
}

.......
.......

```

测试程序修改：
```javascript
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char **argv)
{

    int buf[] = {1,5,9,1,5,9,9};
    int len = sizeof(buf)/sizeof(int);
    int fd;

    if((fd = open("/dev/my_drv",O_RDWR)) < 0)
        printf("/dev/my_drv can't open!\r\n");

    write(fd, buf, len);
    read(fd, buf, len);
    close(fd);

    return 0;

}
```
## 5.1、测试结果
测试结果是出现了问题，只有buf前两个字节正常
![在这里插入图片描述](https://img-blog.csdnimg.cn/20190620194938416.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2E5MzUzNjcyNzY=,size_16,color_FFFFFF,t_70)
## 5.2、分析问题
经过仔细检查发现，我使用driver使用的buf  val是int整数类型要占用4个字节，而copy_from_user传输的是按照拷贝地址和字节数来的，而我使用的长度是只有7的长度，那么意思就是说从开始的地址拷贝7个字节到目标地址。这样子val数组前两个数就已经8个字节了，所以只有前两个数有变化。

## 5.3、BUG解决方案：
		1 把int类型的val改为char类型，以及测试要使用char buf
		2 对int的长度做好处理，长度7的，要乘以sizeof(int)的长度，得出需要拷贝的字节长度。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20190621151225154.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2E5MzUzNjcyNzY=,size_16,color_FFFFFF,t_70)

## 5.4、完整代码修改
驱动的代码
```javascript
#include <linux/cdev.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/uaccess.h>
#include <linux/errno.h>

#define _BUF_MAX 125

static int my_drv_open(struct inode *inode, struct file *fl);
static ssize_t my_read(struct file *rfl, char __user *rbuf, size_t count, loff_t *lf);
static ssize_t my_write(struct file *wfl, const char __user *wbuf, size_t count, loff_t *lf);

static struct file_operations my_drv_fops={
    .open = my_drv_open,
    .read = my_read,
    .write = my_write,
};

static char val[_BUF_MAX] = {0}; //读写buf测试

static int my_drv_open(struct inode *inode, struct file *fl)
{
    printk("my_drv_open\r\n");

    return 0;
}

static ssize_t my_read(struct file *rfl, char __user *rbuf, size_t count, loff_t *lf)
{


    unsigned int buf_len = (unsigned int)(sizeof(val)/sizeof(char));
    unsigned int i;

    if(buf_len < count)
        count = buf_len;

    printk("my_drv read len:%ld\r\n", count);
        
    if(copy_to_user(rbuf, val, count))
    {
        return -EFAULT;
    }

    buf_len = count;
    for(i = 0; i < buf_len;i++)
        printk("my_drv read val[%d]=%d\r\n", i, val[i]);
    
    return 0;
}

static ssize_t my_write(struct file *wfl, const char __user *wbuf, size_t count, loff_t *lf)
{

    unsigned int buf_len = (unsigned int)(sizeof(val)/sizeof(char));
    unsigned int i;

    if(buf_len < count)
        count = buf_len;
    
    printk("my_drv write buf len:%ld\r\n", count);

    if(copy_from_user(val, wbuf, count))
    {
        return -EFAULT;
    }
    
    buf_len = count;
    for(i = 0; i < buf_len;i++)
        printk("my_drv write val[%d]=%d\r\n", i, val[i]);

    return 0;
}

int my_drv_init(void)
{
    int major_id = 100;
    //字符设备注册
    register_chrdev(major_id, "my_drv", &my_drv_fops);

    return 0;
    
}

void my_drv_exit(void)
{
    unregister_chrdev(100, "my_drv");
}


module_init(my_drv_init);
module_exit(my_drv_exit);
MODULE_AUTHOR("cwp");
MODULE_VERSION("0.1.0");
MODULE_LICENSE("GPL");
```

测试代码
```javascript
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char **argv)
{

    char buf[8] ={11,22,33,44,55,66,77,88};
    char rbuf[125];
    int len = sizeof(buf)/sizeof(char);
    int fd;

    if((fd = open("/dev/my_drv",O_RDWR)) < 0)
        printf("/dev/my_drv can't open!\r\n");

    write(fd, buf, len);
    read(fd, rbuf, len);

    close(fd);

    return 0;

}
```
