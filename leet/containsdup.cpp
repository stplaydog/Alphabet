#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <cassert>
#include <iostream>

using namespace std;

class Solution {
    public:
        bool containsNearbyDuplicate(vector<int>& nums, int k) {
            if(nums.size()<2) return false;
            multimap<int, int> m;
            for(int i=0; i<nums.size(); i++)
            {
                m.insert(pair<int, int>(nums[i], i));
            }
            for(multimap<int,int>::iterator i = m.begin(); i != m.end(); ++i)
            {
                std::pair <multimap<int,int>::iterator, multimap<int,int>::iterator> r;
                r = m.equal_range(i->first);

                for(multimap<int,int>::iterator l = r.first; l != r.second; ++l)
                {
                    for(multimap<int,int>::iterator n = r.first; n != r.second; ++n)
                    {
                        if(abs(l->second - n->second)>k)
                            return false;
                    }
                }
            }
            return true;
        }
}

int main(int argc, char* argv[])
{
    vector<int> nums;
    nums.push_back(2);
    nums.push_back(1);

    Solution s;
    cout<<s.containsNearbyDuplicate(nums, 2)<<endl;
}
