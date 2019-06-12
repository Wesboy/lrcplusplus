#include <iostream>

using namespace std;

class Solution {
public:
    int strStr(string haystack, string needle) {

        int len = needle.size();
        int h_len = haystack.size();
        int i;

        if(len == h_len)
        {
            if(haystack == needle)
                return 0;
            else
                return -1;
        }
        
        for(i = 0; i <= h_len-len;i++)
        {
            if(haystack.substr(i, len) == needle)
                return i;
        }
        return -1;
    }
};

int main()
{
	string haystack = "aaa";
	string needle = "a";
	Solution sl;
	
	cout<<"haystack: "<<haystack<<"needle: "<<needle<<endl;
	cout<<"output: "<<sl.strStr(haystack, needle)<<endl;
	
	return 0;
}