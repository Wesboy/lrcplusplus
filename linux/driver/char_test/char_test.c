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

    int i;

    for(i = 0; i < len; i++)
    {
        printf("%d ",rbuf[i]);
    }
    printf("\n");

    close(fd);

    return 0;

}
