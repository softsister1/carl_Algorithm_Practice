/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int maxDepth(TreeNode* root) {
        int depth = 0;
        if (root == NULL) return 0;
        queue<TreeNode*> qu;
        qu.push(root);
        while (!qu.empty()){
            int levelnum = qu.size();
            for (int i = 0; i < levelnum; i++){
                TreeNode* cur = qu.front();
                qu.pop();
                depth++;
                if(cur->left) qu.push(cur->left);
                if(cur->right) qu.push(cur->right);
            }
             
        }
        return depth;
    }
};