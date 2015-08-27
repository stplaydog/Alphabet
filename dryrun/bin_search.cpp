#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <cassert>
#include <iostream>

using namespace std;

struct Node
{
    Node *left;
    Node *right;
    int val;

    Node()
    {
        left = NULL;
        right = NULL;
        val = -1;
    }
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

Node * find_n_separate_right_leftmost(Node *n)
{
    Node *ret = n->right;
    Node *parent = n;

    while(ret->left != NULL)
    {
        parent = ret;
        ret = ret->left;
    }

    if(parent->left == ret)
        parent->left = NULL;
    else
        parent->right = NULL;

    return ret;
}

bool rm(Node *root, int _val)
{
    bool ret = false;
    Node *rm_node = root;
    Node *parent = NULL;
    /* Find the node first */
    while(rm_node != NULL)
    {
        if(rm_node->val == _val)
        {
            break;
        }
        else if(rm_node->val < _val)
        {
            parent = rm_node;
            rm_node = rm_node->right;
        }
        else if(rm_node->val > _val)
        {
            parent = rm_node;
            rm_node = rm_node->left;
        }
    }

    if(rm_node == NULL)
    {
        printf("there is no such element to be removed!\n");
        return ret;
    }

    if(rm_node->left == NULL && rm_node->right == NULL)
    {
        /* has no children */
        /* might be sth wrong here */
        if(parent != NULL)
        {
            if(parent->left == rm_node)
            {
                parent->left = NULL;
            }
            else
            {
                parent->right = NULL;
            }
        }
        delete rm_node;
    }
    else if((rm_node->left != NULL && rm_node->right == NULL))
    {
        /* has one left child */
        if(parent->left == rm_node)
        {
            parent->left = rm_node->left;
        }
        else
        {
            parent->right = rm_node->left;
        }
        delete rm_node;
    }
    else if((rm_node->left == NULL && rm_node->right != NULL))
    {
        /* has one right child */
        if(parent->left == rm_node)
        {
            parent->left = rm_node->right;
        }
        else
        {
            parent->right = rm_node->right;
        }
        delete rm_node;
    }
    else if((rm_node->left != NULL && rm_node->right != NULL))
    {
        /* has two children */
        Node *right_leftmost = find_n_separate_right_leftmost(rm_node);
        if(parent->left == rm_node)
        {
            parent->left->val = right_leftmost->val;
        }
        else
        {
            parent->right->val = right_leftmost->val;
        }
        delete right_leftmost;
    }
}


Node * search(Node *root, int _val)
{
    Node* ret = NULL;
    Node *tmp = root;

    while(tmp != NULL)
    {
        if(tmp->val == _val)
        {
            ret = tmp;
            break;
        }
        else if (tmp->val < _val)
        {
            tmp = tmp->right;
        }
        else
        {
            tmp = tmp->left;
        }
    }
    return ret;
}

void traverse_preorder(Node *root, string &trace)
{
    char arr[1000];
    snprintf(arr, 1000, "%d,", root->val);
    trace += arr;
    if(root->left != NULL)
    {
        traverse_preorder(root->left, trace);
    }
    if(root->right != NULL)
    {
        traverse_preorder(root->right, trace);
    }
}

void traverse_inorder(Node *root, string &trace)
{
    if(root->left != NULL)
    {
        traverse_inorder(root->left, trace);
    }
    char arr[1000];
    snprintf(arr, 1000, "%d,", root->val);
    trace += arr;
    if(root->right != NULL)
    {
        traverse_inorder(root->right, trace);
    }
}

void traverse_postorder(Node *root, string &trace)
{
    if(root->left != NULL)
    {
        traverse_postorder(root->left, trace);
    }
    if(root->right != NULL)
    {
        traverse_postorder(root->right, trace);
    }
    char arr[1000];
    snprintf(arr, 1000, "%d,", root->val);
    trace += arr;
}

int main(int argc, char* argv[])
{
    /* Test insert */
    Node *root = new Node();    
    insert(root, 1);
    insert(root, 4);
    insert(root, 7);
    insert(root, 5);
    insert(root, 8);
    insert(root, 10);
    insert(root, 2);
    insert(root, 15);

    string trace = "";

    /* Test traversal */
    traverse_preorder(root, trace); 
    assert(strcmp(trace.c_str(), "1,4,2,7,5,8,10,15,")==0);
    trace = "";
    traverse_inorder(root, trace);
    assert(strcmp(trace.c_str(), "1,2,4,5,7,8,10,15,")==0);
    trace = "";
    traverse_postorder(root, trace);
    assert(strcmp(trace.c_str(), "2,5,15,10,8,7,4,1,")==0);

    /* Test search */
    assert(search(root, 10)!=NULL);
    assert(search(root, 17)==NULL);

    /* Test rm */
    rm(root, 8);
    trace = "";
    traverse_preorder(root, trace);
    assert(strcmp(trace.c_str(), "1,4,2,7,5,10,15,")==0);

    rm(root, 15);
    trace = "";
    traverse_preorder(root, trace);
    assert(strcmp(trace.c_str(), "1,4,2,7,5,10,")==0);

    rm(root, 4);
    trace = "";
    traverse_preorder(root, trace);
    assert(strcmp(trace.c_str(), "1,5,2,7,10,")==0);

    return 1;
}
