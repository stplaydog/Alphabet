#include <iostream>
#include <cstring>
#include <cassert>

using namespace std;

class IsRotateString 
{
public:
    IsRotateString(const string & a, const string & b)
    {
        string conc = b+b;
        char * find = strstr(conc.c_str(), a.c_str());
        if(find)
            m_res = true;
        else
            m_res = false;
    }

    bool getRes() { return m_res; }
private:
    bool m_res;
};

int main(int argc, char* argv[])
{
    string a1 = "my name is kk";
    string b1 = "name is kkmy ";
    IsRotateString irs1(a1, b1);
    assert(irs1.getRes() == true);
}
