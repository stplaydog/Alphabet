#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>

using namespace std;

struct linklist
{
    int val;
    linklist *next;

    linklist(int _val) : val(_val), next(NULL) {}
};


linklist* reverse_iterative(linklist *head)
{
    if(head == NULL || head->next == NULL)
        return head;

    linklist *p = head->next;
    linklist *pre = head;
    pre->next = NULL;

    while(p != NULL)
    {
        linklist *tmp = p->next;
        p->next = pre;
        pre = p;
        if(tmp == NULL) break;
        p = tmp;
    }

    return p;
}

int main(int argc, char* argv[])
{

    linklist *head = new linklist(2);
    linklist *tail = new linklist(1);
    head->next = tail;

    linklist *reversed = reverse_iterative(head);

    return 1;
}
