#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <cassert>
#include <iostream>

using namespace std;

struct Node
{
    int val;
    Node *next;
};

void push(Node **head, int _val)
{
    Node *n = new Node();
    n->val = _val;

    n->next = *head;
    *head = n;
}

Node * find_middle(Node *head)
{
    Node *ret = head;
    Node *lead = head;
    int count = 1;
    while(lead->next != NULL)
    {
        lead = lead->next;
        ++count;
        if(count%2 == 0 && count/2>1)
        {
            ret = ret->next;
        }
    }
    return ret;
}

int main(int argc, char* argv[])
{
    Node *head = new Node();
    push(&head, 1);
    push(&head, 3);
    push(&head, 4);
    push(&head, 5);
    push(&head, 7);
    push(&head, 10);
    push(&head, 16);
    push(&head, 2);

    Node *mid = find_middle(head);

    assert(mid->val == 7);
    return 1;
}
