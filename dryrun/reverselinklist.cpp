#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>

struct linklist
{
    int val;
    linklist *next;
};


void reverse_iterative(linklist *head)
{
    if(head == NULL)
    {
        cout<<"there is no elem to reverse!"<<endl;
        return;
    }
    linklist *p = head->next;
    linklist *pre = head;

    while(p->next != NULL)
    {
        linklist *tmp = p->next;
        p->next = pre;
        pre = p;
        p = tmp;
    }
}

int main(int argc, char*[] argv)
{
    return 1;
}
