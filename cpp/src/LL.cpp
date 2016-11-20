#include "utils.h"

template <typename T>
bool insertInFront( LNode<T> **head, T data )
{ 
    LNode<T> *l = new LNode<T>(data);
    if(!l) return false;
    l->m_next = *head;
    *head   = l; // Incorrect! return true;
    return true;
}

template <typename T>
LNode * find(LNode<T> *head, T data)
{
    LNode*
    while(head && )
}

int main(int argc, char* argv[])
{
    vector<int> v1 = {1,2,3,4,5,6,7,8,9,10};
    LNode<int> *l1 = new LNode<int>(v1);
    insertInFront(&l1, 0);
    l1->dump();

    return 0;
}


