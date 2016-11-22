#include <iostream>
#include <cassert>

using namespace std;

class CheckAnagram
{
public:

    CheckAnagram(const string & a, const string & b)
        : m_a(a), m_b(b)
    {
    }

    bool isAnagram()
    {
        int cnt[256];
        memset(cnt, sizeof(int)*256, 0);
        if(m_a.size() != m_b.size())
            return false;

        int len = m_a.size();

        for(int i=0; i<len; i++)
        {
            int idx = m_a[i] - 0;
            cnt[idx]++;
        }

        for(int i=0; i<len; i++)
        {
            int idx = m_b[i] - 0;
            if(!cnt[idx]--)
                return false;
        }
        return true;
    }

private:
    string m_a;
    string m_b;
};

int main(int argc, char* argv[])
{
    string a1 = "abcd";
    string b1 = "bcad";
    CheckAnagram ca1(a1, b1);
    assert(ca1.isAnagram() == true);

    string a2 = "abcd";
    string b2 = "cad";
    CheckAnagram ca2(a2, b2);
    assert(ca2.isAnagram() == false);

    string a3 = "abcd";
    string b3 = "cadd";
    CheckAnagram ca3(a3, b3);
    assert(ca3.isAnagram() == false);
    return 0;
}
