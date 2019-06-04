#include <iostream>

using namespace std;

//大端：数据高字节存放在低地址，低字节存放在高地址
//小端: 数据低字节存放在低地址，高字节存放在高地址

int main(void)
{
	char array[12] = {0x01 , 0x02 , 0x03 , 0x04 , 0x05 , 0x06 , 0x07 , 0x08};     
	short *pshort = (short *)array;     
	int *pint = (int *)array;     
	//int64 *pint64 = (int64 *)array;    

	printf("0x%x , 0x%x , 0x%llx", *pshort , *(pshort+2) , *(pint+2));
	return 0;
}
