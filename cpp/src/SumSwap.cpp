#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <utility>
#include <algorithm>
#include <numeric>

using namespace std;

class SumSwap
{
public:

    SumSwap(const vector<int> & a, const vector<int> & b)
    {
        m_a = a;
        m_b = b;
    }

    pair<int, int> find_bf()
    {
        int sum1 = accumulate(m_a.begin(), m_a.end(), 0);
        int sum2 = accumulate(m_b.begin(), m_b.end(), 0);
        m_tgt   = (sum1 - sum2)/2;
        return brute_force();
    }

    pair<int, int> brute_force()
    {
        pair<int, int> ret(-1,-1);
        for(int i=0; i<m_a.size(); i++)
        {
            for(int j=0; j<m_b.size(); j++)
            {
                if(m_a[i]-m_b[j] == m_tgt)
                {
                    ret = pair<int, int>(i, j);
                    return ret; 
                }
            }
        }
        return ret;
    }

private:
    vector<int> m_a;
    vector<int> m_b;
    int         m_tgt;
};

int main(int argc, char *argv[])
{
    vector<int> a1 = {1,6,3,4,5,2};
    vector<int> b1 = {1,6,4,3,9,2};
    SumSwap ss1(a1, b1);

    pair<int, int> res1 = {0, 3};
    assert(ss1.find_bf() == res1);

    //
    vector<int> a2 = {1,6,3,4,5,2};
    vector<int> b2 = {100,6,4,3,9,2};
    SumSwap ss2(a2, b2);

    pair<int, int> res2 = {-1, -1};
    assert(ss2.find_bf() == res2);

    //
    vector<int> a3 = {};
    vector<int> b3 = {};
    SumSwap ss3(a3, b3);

    pair<int, int> res3 = {-1, -1};
    assert(ss3.find_bf() == res3);

    //
    vector<int> a4 = {1,1,1,1,1,1};
    vector<int> b4 = {1,2,2,1,1,1};
    SumSwap ss4(a4, b4);

    pair<int, int> res4 = {0, 1};
    assert(ss4.find_bf() == res4);
}
