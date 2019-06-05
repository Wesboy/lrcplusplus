/**
*	题目：将一个String转化为int（atoi），String转换int，两个注意点，一是正负数的判断，二是注意int值的范围
*
**/

#include <iostream>
#include <string>
#include <cstring>

using namespace std;
using std::string;

int power(int num, int co)
{
	int ret = num;
	while(co--)
	{ 
		ret *= 10; 
	}
	return ret;
}

//int 最大值：2147483647‬ 最小值：-2147483648
int atoi(string str)
{
	int ret = 0;
	int str_len = str.length();
	int int_len = 11;
	int i;
	cout<<str_len<<endl;
	//符号判断
	if(str_len<0 || int_len < str_len)
		return 0;
	
	i = 0;
	if(str[0] == '-')
	{
		i++;
	}
	while(i < str_len)
	{
		if(str[i] < '9' && str[i] > '0')
		{
			ret += power((str[i]-0x30), str_len-i-1);
		}
		i++;
	}
	
	if(str[0] == '-')
	{
		ret = 0-ret;
		
	}
	return ret;
}

int main(int argc, char **argv)
{
	string str_test;
	int ret = 0;
	int i;
	
	cout<<"string num ="<<argv[1]<<endl;
	
	if(argc == 2)
	{
		str_test = argv[1];
	}
	
	ret = atoi(str_test);
	cout<<"num ="<<ret<<endl;
	
	return 0;
}