#include <iostream>
#include <string>
#include <memory>
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <vector>

using namespace std;

class UniqueChars
{
public:
    UniqueChars()
    {
        m_bitvec.resize(16, 0);
    }

    bool isUnique(const string & input)
    {
        fill(m_bitvec.begin(), m_bitvec.end(), 0);

        for(auto iter = input.begin(); iter != input.end(); ++iter)
        {
            char c = *iter;
            int offset = c - 0;
            int i = offset / 8;
            int j = offset % 8;
            if(m_bitvec[i] & (1<<j))
                return false;
            m_bitvec[i] |= 1<<j;
        }
        return true;
    }

private:
    vector<char> m_bitvec;
};


int main(int argc, char* argv[])
{
    UniqueChars uc;

    string t1 = "abzACDZ!#$%$^&&";
    string t2 = "abzACDZ";
    assert(uc.isUnique(t1) == false);
    assert(uc.isUnique(t2) == true);
    return 0;
}
