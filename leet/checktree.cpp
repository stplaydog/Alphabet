class Solution {
    public:
        bool isSameTree(TreeNode* p, TreeNode* q) {
            bool ret = false;
            if(((p->left==NULL && q->right==NULL) && (p->left==NULL && q->right==NULL))
              || ((p->left!=NULL && q->right!=NULL) && (p->left==NULL && q->right==NULL))
              || ((p->left==NULL && q->right==NULL) && (p->left!=NULL && q->right!=NULL))
              || ((p->left!=NULL && q->right!=NULL) && (p->left!=NULL && q->right!=NULL)))
            {
                ret = true;
            }
            if(ret ==true && p->left != NULL)
            {
                ret = isSameTree(p->left, q->left);
            }
            if(ret ==true && p->right != NULL)
            {
                ret = isSameTree(p->right, q->right);
            }
            return ret;
        }
};
