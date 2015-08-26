/**/
struct Node
{
    int val;
    Node *next;
};

Node * find_middle(Node *head)
{
    Node *ret = head;
    Node *lead = head;
    int count = 0;
    while(lead->next != NULL)
    {
        lead = lead->next;
        ++count;
        if(count%2 == 0 && count/2>0)
        {
            ret = ret->next;
        }
    }
    return ret;
}

