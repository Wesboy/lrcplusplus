/**************************************************************************
Given a sorted array nums, remove the duplicates in-place such that each element appear only once and return the new length.

Do not allocate extra space for another array, you must do this by modifying the input array in-place with O(1) extra memory.

Example 1:

Given nums = [1,1,2],

Your function should return length = 2, with the first two elements of nums being 1 and 2 respectively.

It doesn't matter what you leave beyond the returned length.
Example 2:

Given nums = [0,0,1,1,1,2,2,3,3,4],

Your function should return length = 5, with the first five elements of nums being modified to 0, 1, 2, 3, and 4 respectively.

It doesn't matter what values are set beyond the returned length.
**************************************************************************/


#include <iostream>
#include <vector>


using namespace std;


class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        int strnum = strs.size();
        string ret;

        int len;
        int i;
        int comlen = 0;
        int start = 0;
        string str;

        if(strnum < 1)
            return ret;
        else if(strnum == 1)
            return strs[0];

        if(strs[0].size() > strs[1].size())
            len = strs[0].size();
        else
            len = strs[1].size();
        if(len < 1)
            return ret;

        for(i = 0; i < len; i++)
        {
            if(strs[0][i] == strs[1][i]){
            //    if(start - i > 1){
             //      comlen = 0;
             //   }
                comlen++;
            }
            else
                break;
        }
        if(comlen < 1)
            return ret;

        ret.assign(strs[0], start, start+comlen);
        //cout<<ret<<endl;
        while(strnum > 2)
        {
            for(;;)
            {
                str = strs[strnum-1].substr(start, start+comlen);

                if(strs[strnum-1].substr(start, start+comlen) != ret.substr(0, comlen))
                {
                    if(comlen > 0)
                        comlen--;
                    else
                        break;
                }
                else
                    break;
            }
            strnum--;
        }
        ret.assign(strs[0], start, start+comlen);

        return ret;
    }
};

int main()
{
    int i;
    string str = "acb";
    string str1 = "bda";
    Solution sl;

    vector<string> p;
    p.push_back(str);
    p.push_back(str1);

    cout<<sl.longestCommonPrefix(p)<<endl;

    return 0;
}
