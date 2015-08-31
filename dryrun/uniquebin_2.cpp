/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
    public:
        vector<TreeNode*> generateTrees(int n) {
            if(n == 0)  return vector<TreeNode *>(1, NULL);
            vector<vector<vector<TreeNode*>>> subtree(n+2, vector<vector<TreeNode*>>(n+2, vector<TreeNode*>()));
            for(int i=1; i<=n+1; ++i){
                subtree[i][i].push_back(new TreeNode(i));
                subtree[i][i-1].push_back(NULL);    
            }
            for(int l=2; l<=n; ++l){
                for(int i=1; i<=n-l+1; ++i){
                    for(int j=i; j<=i+l-1; ++j){
                        for(int k=0; k<subtree[j+1][i+l-1].size(); ++k){
                            for(int m=0; m<subtree[i][j-1].size(); ++m){
                                TreeNode *T = new TreeNode(j);
                                T->left = subtree[i][j-1][m];
                                T->right = subtree[j+1][i+l-1][k];
                                subtree[i][i+l-1].push_back(T);    
                            }
                        }
                    }
                }
            }
            return subtree[1][n];
        }
};
