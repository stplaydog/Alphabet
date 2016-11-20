#include "utils.h"

template <typename T>
T beginOfLoop(LNode<T> *l1)
{
    LNode<T> *go1 = l1;
    LNode<T> *go2 = l1;
    LNode<T> *go3 = l1;

    do
    {
        go1 = go1->m_next;
        go2 = go2->m_next->m_next;
    }
    while(go1 != go2);

    while(go3 != go1)
    {
        go3 = go3->m_next;
        go1 = go1->m_next;
    }

    return go3->m_value;
}


int main(int argc, char*argv[])
{
    vector<int> v1 = {1,2,3,4,5,6,7,8,9,10};
    LNode<int> *l1 = new LNode<int>(v1, 3);
    cout<<beginOfLoop(l1)<<endl;
    return 0;
}
