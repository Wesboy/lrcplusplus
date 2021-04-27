class Solution {
public:
    int myAtoi(string s) {
        int str_len = s.length();//
        if(str_len <= 0)
            return 0;

        int i = 0;
        long ret = 0;
        char first_char = 0;

        while((s[i]!= 0) && (str_len-- != 0))
        {
            if(first_char == 0)
            {
                if(s[i] == 0x20)//space
                {

                }
                else if(s[i] == '-')
                {
                    first_char = -1;
                }
                else if(s[i] == '+')
                {
                    first_char = 1;
                }
                else if(s[i] >= 0x30 && s[i] <= 0x39)
                {
                    first_char = 2;
                    ret *= 10;
                    ret += (s[i] - 0x30);
                }
                else
                {
                    ret = 0;
                    break;
                }
            }
            else
            {
                if(s[i] >= 0x30 && s[i] <= 0x39)
                {
                    ret *= 10;
                    ret += (s[i] - 0x30);
                    if(ret > 2147483647)
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
            i++;
        }

        if(first_char == -1)
        {
            if(ret > 2147483648)
                ret = 2147483648;
            ret *= -1;
        }
        else if(ret > 2147483647)
                ret = 2147483647;
        return (int)ret;
    }
};