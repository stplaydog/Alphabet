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

    bool match1()
    {
        bool ret = false;
        for(int i=1; i<m_value.length(); ++i)
        {
            try{
                string m = m_value.substr(0, i);
                string n = get_n(m);
                string built = buildString(m, n);
                if(built == m_value)
                {
                    ret =  true;
                    break;
                }
            }
            catch(...)
            {
               continue; 
            }
        }
        return ret;
    }

    string get_n(const string& m)
    {
        string ret;
        int num_main = 0;
        for(int i=0; i<m_pattern.size(); i++)
        {
            if(m_pattern[i] == m_pattern[0])
            {
                num_main++;
            }
        }

        int num_alt = m_pattern.length() - num_main;
        int length_alt = (m_value.length() - num_main * m.length()) / num_alt;

        char alter = m_pattern[0] == 'a' ? 'b' : 'a';

        for(int i=0, j=0; i<m_pattern.length(); i++, j+= m.length())
        {
            if(m_pattern[i] == alter)
            {
                ret = m_value.substr(j, length_alt);
                break;
            }
        }
        return ret;
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

    assert(pm1.match1() == true);
    assert(pm2.match1() == false);
}
