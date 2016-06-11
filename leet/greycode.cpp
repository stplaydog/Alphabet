#include <vector>
#include <map>
#include <cmath>

using namespace std;

class Solution {
    public:
        vector<int> grayCode(int n) {
            map<int, bool> m;            
            vector<int> ret;
            ret.push_back(0);
            m[0] = true;
            int num = (int)pow(2,n);
            while(ret.size()<num)
            {
                for(int i=1; i<num; i++)
                {
                    if(m.find(i) == m.end())
                    {
                        int num = ret.back();
                        if(NumberOfSetBits(num^i)==1)
                        {
                            m[i] = true;
                            ret.push_back(i);
                            break;
                        }
                    }
                }
            }
            return ret;
        }

        int NumberOfSetBits(int i)
        {
            i = i - ((i >> 1) & 0x55555555);
            i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
            return (((i + (i >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
        }

};

int main(int argc, char* argv[])
{
    Solution s;
    s.grayCode(2);
    return 1;
}
