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
    int minDepth(TreeNode* root) {
        int depth = 0;
        queue<TreeNode*> qu;
        if (!root) return 0;
        qu.push(root);
        while (!qu.empty()){
            int levelnum  = qu.size();
            depth++;
            for (int i = 0; i < levelnum; i++){
                TreeNode* cur = qu.front();
                qu.pop();
                if (cur->left); qu.push(cur->left);
                if (cur->right); qu.push(cur->right);
                if(!cur->left && !cur->right) return depth;
            }
        }
        return depth;
    }
};