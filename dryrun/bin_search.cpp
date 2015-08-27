#include <stdio.h>
#include <stdlib.h>

struct Node
{
    Node *left;
    Node *right;
    int val;
};

void insert(Node *root, int _val)
{
    Node *tmp = root;
    bool success = false;
    while(success == false)
    {
        if(tmp->val == -1 || tmp->val == _val)
        {
            tmp->val = _val;
            success = true;
        }
        else if (tmp->val < _val)
        {
            if(tmp->right == NULL)
            {
                tmp->right = new Node();
                tmp->right->val = _val;
                success = true;
            }
            else
            {
                tmp = tmp->right;
            }
        }
        else if(tmp->val > _val && tmp->left == NULL)
        {
            if(tmp->left == NULL)
            {
                tmp->left = new Node();
                tmp->left->val = _val;
                success = true;
            }
            else
            {
                tmp = tmp->left;
            }
        }
    }
}

bool rm(Node *root, int _val)
{
}

bool search(Node *root, int _val)
{
}

void _traverse_preorder(Node *root)
{
}

void _traverse_inorder(Node *root)
{
}

void _traverse_postorder(Node *root)
{
}

int main(int argc, char*[] argv)
{
    return 1;
}
