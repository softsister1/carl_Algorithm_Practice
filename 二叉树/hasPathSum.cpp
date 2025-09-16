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
    bool hasPathSum(TreeNode* root, int targetSum) {
        if(!root) return false;
        return backtrack(root, targetSum - root->val);
    }

    bool backtrack(TreeNode* cur, int count){
            if (!cur->left && !cur->right && count == 0) return true;
            if (!cur->left && !cur->right) return false;
            if (cur->left){
                if(backtrack(cur->left, count - cur->left->val)) return true;
            }
            if (cur->right){
                if(backtrack(cur->right, count - cur->right->val)) return true;
            }
            return false;
    }

}
};