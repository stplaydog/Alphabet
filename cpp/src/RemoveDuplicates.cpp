#include <iostream>
#include <cassert>
#include <vector>


using namespace std;

class RemoveDuplicates
{
public:
    RemoveDuplicates(const string &input)
    {
        m_rmvd = input;
    }

    string remove_duplicates()
    {
        int lead = 0;
        int tail = 0;

        while(lead != m_rmvd.size())
        {
           if(lead ==0 || !check_dup(lead)) 
               m_rmvd[tail++] = m_rmvd[lead++];
           else
               lead++;
        }
        return m_rmvd.substr(0, tail);
    }

    bool check_dup(int lead)
    {
        char tobe_checked = m_rmvd[lead];
        for(int i=lead-1; i>=0; i--)
        {
            if(m_rmvd[i] == tobe_checked)
            {
                return true;
            }
        }
        return false;
    }

private:
    string m_rmvd;
};

int main(int argc, char* argv[])
{
    string s1 = "abcd";
    RemoveDuplicates rd1(s1);
    assert(rd1.remove_duplicates() == s1);

    string s2 = "abbcdd";
    RemoveDuplicates rd2(s2);
    assert(rd2.remove_duplicates() == "abcd");

    string s3 = "";
    RemoveDuplicates rd3(s3);
    assert(rd3.remove_duplicates() == "");

    string s4 = "abcdabcd";
    RemoveDuplicates rd4(s4);
    assert(rd4.remove_duplicates() == "abcd");
    return 0;
}
