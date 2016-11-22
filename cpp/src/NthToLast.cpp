#include "utils.h"

template <typename T>
T nThToLast(LNode<T> *head, int n)
{
    assert(n>=0);
    LNode<T> *go = head;
    LNode<T> *fl = head;
    int i=0;

    while(go && i<n)
    {
        go = go->m_next;
        i++;
    }

    while(go)
    {
        go = go->m_next;
        fl = fl->m_next;
    }

    return i==n ? fl->m_value : -1; 
}

int main(int argc, char* argv[])
{
    vector<int> v1 = {1,2,3,4,5,6};
    LNode<int> *ln1 = new LNode<int>(v1);
    cout<<nThToLast(ln1, 3)<<endl;
}

