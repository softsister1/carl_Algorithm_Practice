#include<vector>
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
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> result;
        preorderhelpfun(root, result);
        return result;

        
    }
    void preorderhelpfun(TreeNode* root, vector<int>& result){
        if (root == nullptr) return;
        result.push_back(root->val);
        preorderhelpfun(root->left, result);
        preorderhelpfun(root->right, result);
    }
};