#include <vector>
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
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        inorderHelper(root, result);  
        return result; 
           
    }
    void inorderHelper(TreeNode* node, vector<int>& result) {
        if (node == nullptr) return;
        
        inorderHelper(node->left, result);    // 先遍历左子树
        result.push_back(node->val);          // 再处理根节点
        inorderHelper(node->right, result);   // 最后遍历右子树
    }
};