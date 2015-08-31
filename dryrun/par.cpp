#include <iostream>

using namespace std;


class Solution {
    public:
        bool isPalindrome(int x) {

            int rev =0;

            while(x>0)
            {
                int res = x % 10;
                rev = rev *10 + res;
                x = x/10;
            }

            cout<<rev<<endl;

            if(rev == x)
                return true;
            else
                return false;
        }
};

int main(int argc, char *argv[])
{
    Solution s;
    s.isPalindrome(1);
}
