#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <cassert>
#include <iostream>
#include <cmath>

using namespace std;


class Solution {
    public:
        string addBinary(string a, string b) {
            string ret;
            int i=a.length()-1;
            int j=b.length()-1;

            bool add= false;
            while(i>=0 && j>=0)
            {
                if(a[i]=='0' && b[j]=='0')
                {
                    ret = '0'+ret;
                }
                else if((a[i]=='1'&&b[j]=='0') || (a[i]=='0'&&b[j]=='1'))
                {
                    if(!add){ 
                        ret = '1'+ret;
                        add = false;
                    }
                    else
                    {
                        ret = '0' + ret;
                        add = true;
                    }
                }
                else if(a[i]=='1' && b[j]=='1')
                {
                    if(add)
                    { 
                        ret = '1'+ret;
                        add = true;
                    }
                    else
                    {
                        ret = '0' + ret;
                        add = true;
                    }
                }
                i--;
                j--;
            }
            while(i>=0)
            {
                if(a[i]=='1')
                {
                    if(add) {ret = '0' + ret; add = true;}
                    else {ret = '1'+ret; }
                }
                else if(a[i]=='0')
                {
                    if(add) {ret = '1' + ret; add = false;}
                    else ret = '0'+ret;
                }
                i--;
            }

            while(j>=0)
            {
                if(b[j]=='1')
                {
                    if(add) {ret = '0' + ret; add = true;}
                    else {ret = '1'+ret; }
                }
                else if(b[j]=='0')
                {
                    if(add) {ret = '1' + ret; add = false;}
                    else ret = '0'+ret;
                }
                j--;
            }

            if(add) ret = '1'+ret;
            return ret;
        }


};

int main(int argc, char* argv[])
{
    //string s1 = "10100000100100110110010000010101111011011001101110111111111101000000101111001110001111100001101";
    //string s2 = "110101001011101110001111100110001010100001101011101010000011011011001011101111001100000011011110011";
    string s1 = "1010";
    string s2 = "1011";
    Solution s;
    string r = s.addBinary(s1, s2);
    return 1;
}
