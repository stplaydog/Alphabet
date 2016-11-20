#include "utils.h"


template <typename T>
void removeDupUnsortedLL(LNode<T> *head)
{
    LNode<T> *go  = head;
    LNode<T> *pre = head;
    set<T> st;

    while(go)
    {
        if(st.find(go->m_value) == st.end())
        {
            st.insert(go->m_value);
            pre = go == head ? pre : pre->m_next;
            go  = go->m_next;
        }
        else
        {
            LNode<T> *ptr = go;
            pre->m_next = go->m_next;
            go  = go->m_next;
            delete ptr;
        }
    }

}

int main(int argc, char* argv[])
{
    vector<int> v1  = {1,1,2,3,4,6,3,7,5,4};
    LNode<int> *ln1 = new LNode<int>(v1);
    removeDupUnsortedLL(ln1);
    ln1->dump();

    vector<int> v2  = {1};
    LNode<int> *ln2 = new LNode<int>(v2);
    removeDupUnsortedLL(ln2);
    ln2->dump();

    return 0;
}
