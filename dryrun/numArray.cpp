#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

class NumArray {
    public:
        vector<int> num;
        vector<int> BIT;
        int n;

        NumArray(vector<int> &nums) {
            num = nums;

            n = nums.size();
            BIT = vector<int>(n+1);
            for (int i = 0; i < n; i++)
                init(i, nums[i]);
            for(auto x : BIT)
                cout<<x<<" ";
            cout<<endl;
        }

        void init(int i, int val) {
            i++;
            while (i <= n) {
                //bitset<32> x(i);
                //bitset<32> x1(-i);
                //cout<<i<<":"<<x<<":"<<x1<<" ";
                BIT[i] += val;
                i += (i & -i);
            }
            //cout<<endl;
        }

        void update(int i, int val) {
            int diff = val - num[i];
            num[i] = val;
            init(i, diff);
        }

        int getSum(int i) {
            int sum = 0;
            i++;
            while (i > 0) {
                cout<<i<<":"<<BIT[i]<<endl;
                sum += BIT[i];
                i -= (i & -i);
            }
            return sum;
        }


        int sumRange(int i, int j) {
            return getSum(j) - getSum(i - 1);
        }
};

int main(int argc, char* argv[])
{
    vector<int> nums{1,4,5,7,3,2,8,9,7,7,3,2,8,6};
    NumArray a(nums);

    cout<<"===================="<<endl;
    //cout<<a.sumRange(1,11)<<endl;
    //a.update(3,10);
    //cout<<a.sumRange(1,11)<<endl;
    cout<<a.getSum(7)<<endl;

    return 1;
}
