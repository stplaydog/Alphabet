#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cassert>
#include <queue>

using namespace std;

class Utils
{
public:
    static void dump(const vector<vector<int>> &vec)
    {
        size_t n = vec.size();
        for(size_t i=0; i<n; i++)
        {
            for(size_t j=0; j<n; j++)
            {
                cout<<vec[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
    }

    static void dump(const vector<int> & vec)
    {
        for(int i=0; i<vec.size(); i++)
            cout<<vec[i]<<" ";
        cout<<endl;
    }
};

template <typename T>
struct LNode
{
    LNode(T value)
        : m_value(value), m_next(NULL)
    {
    }

    LNode(vector<T> v, int cir = -1)
    {
        LNode *tmp = this;
        for(int i=0; i<v.size(); i++)
        {
            if(i != 0)
            {
                LNode *newNode = new LNode(v[i]);
                tmp->m_next    = newNode;
                tmp            = newNode;
            }
            else
            {
                tmp->m_value = v[i];
                tmp->m_next  = NULL;
            }
        }

        if(cir != -1)
        {
            LNode *tmp1 = this;
            for(int i=0; i<cir-1; i++)
                tmp1 = tmp1->m_next;
            LNode *tmp2 = this;
            while(tmp2->m_next)
                tmp2 = tmp2->m_next;
            tmp2->m_next = tmp1; 
        }
    }

    

    void dump()
    {
        LNode *tmp = this;
        while(tmp)
        {
            cout<<tmp->m_value<<" "<<flush;
            tmp = tmp->m_next;
        }
        cout<<endl;
    }
    T       m_value;
    LNode * m_next;
};
