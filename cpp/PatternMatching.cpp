#include <iostream>
#include <string>
#include <cassert>

using namespace std;

class PatternMatching
{
public:
    PatternMatching(const string &value, const string &pattern)
    : m_value(value), m_pattern(pattern) 
    {
    }
    
    bool matchBruteForce()
    {
        string la;
        string lb;
        for(int i=0; i<m_value.length(); i++)
        {
            string m = m_value.substr(0, i);
            for(int j=i; j<m_value.length(); j++)
            {
                for(int k=j; k<m_value.length(); k++)
                {
                    string n = m_value.substr(j, k);
                    //cout<<m<<" "<<n<<endl;
                    string built = buildString(m, n);
                    if(built == m_value)
                        return true;
                }
            }
        }
        return false;
    }

    string buildString(const string &m, const string & n)
    {
        char main_letter = m_pattern[0];
        string ret;
        for(int i=0; i<m_pattern.length(); i++)
        {
           if(m_pattern[i] == main_letter) 
               ret += m;
           else
               ret += n;
        }
        return ret;
    }
private:
    string m_value;
    string m_pattern;
};


int main(int argc, char* argv[])
{
    string v1 = "catcatdogdog";
    string p1 = "aabb";
    string v2 = "catcatdogdag";
    string p2 = "aaba";

    PatternMatching pm1(v1, p1);
    PatternMatching pm2(v2, p2);

    assert(pm1.matchBruteForce() == true);
    assert(pm2.matchBruteForce() == false);
}
