#include <iostream>
#include <cassert>
#include <vector>
#include <set>

using namespace std;

class T2
{
public:
    T2(const set<string> & dic)
        : m_pad{{},{},{'a', 'b', 'c'},{'d','e','f'},{'g','h','i'},{'j','k','l'},{'m','n','o'},{'p','q','r','s'},{'t','u','v'},{'w','x','y','z'}}
    {
        m_dic = dic;
    }

    vector<string> get_list(const vector<int> & nums)
    {
        vector<string> ret;
        string built;
        helper(nums, built, ret);
        return ret;
    }

    void helper(const vector<int> & nums, string& built, vector<string> &ret)
    {
        if(built.length() == nums.size())
        {
            if(m_dic.find(built) != m_dic.end())
            {
                ret.push_back(built);
            }
            return;
        }
        for(int i=0; i<=9; i++)
        {
            for(int j=0; j<m_pad[i].size(); j++)
            {
                built += m_pad[i][j];
                helper(nums, built, ret);
                built.pop_back();
            }
        }
    }

private:
    vector<vector<char>> m_pad;
    set<string>          m_dic;
};

int main(int argc, char* argv[])
{
    set<string> dic{"tree", "used"};
    T2 t2(dic);
    vector<string> compare = {{"tree"},{"used"}};

    vector<int> input = {8,7,3,3};
    assert(t2.get_list(input) == compare);
}
