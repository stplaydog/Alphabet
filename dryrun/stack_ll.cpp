#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <csassert>


struct node 
{
    int val;
    node *next;
};


void push(node *head, int _val)
{
    node *n = new node();
    n->val = _val;

    n->next = head;
    head = n;
}

node* pop(node *head, int _val)
{
    node *ret = head;
    head = head->next;
    return ret; 
}


