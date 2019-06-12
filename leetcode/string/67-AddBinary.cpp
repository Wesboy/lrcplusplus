/**
	67. Add Binary

	Given two binary strings, return their sum (also a binary string).

	The input strings are both non-empty and contains only characters 1 or 0.

	Example 1:

	Input: a = "11", b = "1"
	Output: "100"
	Example 2:

	Input: a = "1010", b = "1011"
	Output: "10101"

**/



#include <iostream>

using namespace std;

class Solution {
public:
    string addBinary(string a, string b) {
        string ret;
        char flag = 0;
		
		int a_len = a.length();
		int b_len = b.length();
		int i;
		char tmp;
		
		cout<<"a len:"<<a_len<<"  b len:"<<b_len<<endl;
		cout<<"a  :"<<a<<endl;
		cout<<"b  :"<<b<<endl;
		
		while(1)
		{
			if(a_len > b_len)
			{
				if(b_len <= 0)
					break;
			}
			else
			{
				if(a_len <= 0)
					break;
			}
			a_len--;
			b_len--;
			
			if(a[a_len] == '1' && b[b_len] == '1')
			{
				if(flag)
					ret = char('1') + ret;
				else
					ret = char('0') + ret;
				flag = 1;
			}
			else if(a[a_len] == '1' || b[b_len] == '1')
			{
				if(flag){
					ret = char('0') + ret;
				}
				else{
					ret = char('1') + ret;
				}
			}
			else
			{
				if(flag)
					ret = char('1') + ret;
				else
					ret = char('0') + ret;
				flag = 0;
			}
		}
		
		for(a_len--;a_len>=0;a_len--)
		{
			if(a[a_len] == '1')
			{
				if(flag)
					ret = char('0') + ret;
				else
					ret = char('1') + ret;
			}
			else
			{
				if(flag)
					ret = char('1') + ret;
				else
					ret = char('0') + ret;
				flag = 0;
			}
		}
		for(b_len--;b_len>=0;b_len--)
		{
			if(b[b_len] == '1')
			{
				if(flag)
					ret = char('0') + ret;
				else
					ret = char('1') + ret;
			}
			else
			{
				if(flag)
					ret = char('1') + ret;
				else
					ret = char('0') + ret;
				flag = 0;
			}
		}
		if(flag)
			ret = char('1') + ret;

        return ret;
    }
};

#define TEST_1 1

int main()
{
    Solution sl;
#if TEST_1	
	string a = "11";
	string b = "1";
#else
    string a = "10100000100100110110010000010101111011011001101110111111111101000000101111001110001111100001101";

    string b = "110101001011101110001111100110001010100001101011101010000011011011001011101111001100000011011110011";
#endif
    cout<<"add:"<<sl.addBinary(a, b)<<endl;


    return 0;
}
