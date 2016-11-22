#include <iostream>
#include <cassert>
#include <cstdlib>

using namespace std;

class ReplaceSpace
{
public:
    ReplaceSpace(const char* input)
    {
        m_spaceFree = new char[100];
        int len = strlen(input);
        memcpy(m_spaceFree, input, len);
    }

    ~ReplaceSpace()
    {
        delete [] m_spaceFree;
    }

    char * replace_space()
    {
        int len    = strlen(m_spaceFree);
        int newLen = 0;
        for(int i=0; i<len; i++) 
        {
            if(m_spaceFree[i] == ' ')
                newLen += 2;
        }
        newLen += len-1;
        for(int i=len-1; i>=0; i--)
        {
            if(m_spaceFree[i] == ' ')
            {
                m_spaceFree[newLen--] = '0';
                m_spaceFree[newLen--] = '2';
                m_spaceFree[newLen--] = '%';
            }
            else
                m_spaceFree[newLen--] = m_spaceFree[i];
        }
        return m_spaceFree;
    }

private:
    char * m_spaceFree;
};

int main(int argc, char* argv[])
{
    string s1 = "I think this is a good idea.";
    char *input = new char[100];
    memcpy(input, s1.c_str(), strlen(s1.c_str()));
    ReplaceSpace rs1(input);
    cout<<rs1.replace_space()<<endl;
}
