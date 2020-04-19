#include <stdio.h>

int myAtoi(char * str){
	
    int result = 0;
    if(str == NULL)
        return 0;	
    
    char *p = str;
	unsigned long ret = 0;
	char bNumber = 0;
	char bps = 0;

    if((str[0] < '0' || str[0] > '9') && str[0] != ' ' && str[0] != '-' && str[0] != '+')
	{
		return 0;	
	}
	
	while(*p != 0)
	{
		if(*p >= '0' && *p <= '9')
		{
			ret *= 10;
			ret += (*p - 0x30); 
			if(bps)
			{
				if(ret > 0x80000000)
					return 0x80000000;
				else
					result = ret * (-1);
			}
			else
			{
				if(ret > (0x80000000-1))
					return (0x80000000-1);
				else
					result = ret;
			}
			bNumber = 1; 
		}
		else if(*p == '-')
		{
			if(bNumber == 0)
				bps = 1;
			else
				break;
			bNumber = 1;
		}
		else if(*p == '+')
		{
			if(bNumber)
				break;
			bNumber = 1;
		}
		else if(*p == '.' || (*p >= 'A' && *p <= 'Z') || (*p >= 'a' && *p <= 'z'))
		{
			break;
		}
		else 
		{
			if(bNumber)
				break;
		}
		
		p++;
	}
	
	return result;
}

void main(void)
{
	/*"42"
		"-43"
		"erer"
		"12345678890"
		"dd454545 "
		"223123dfds"
		"-1241242124"
		"-912834723"
		"-91283472332"
		"-9.1283472332"
		"+-4"
		"-+5"
		"  -0012a42"
		"-5-"
		"-6+"
		" b11228552307"
		*/
	char str[] = " b11228552307";
	
	printf("str num :%d\r\n", myAtoi(str));
}