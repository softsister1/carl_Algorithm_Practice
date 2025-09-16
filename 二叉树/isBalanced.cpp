/*
给定一个二叉树，判断它是否是 平衡二叉树  
示例 1：
输入：root = [3,9,20,null,null,15,7]
输出：true
示例 2：


输入：root = [1,2,2,3,3,null,null,4,4]
输出：false
示例 3：

输入：root = []
输出：true
*/

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
    bool isBalanced(TreeNode* root) {
        int result = checkBaBalanced(root);
        if (result > 0) {
            return true;
        }else if (result == -1){
            return false;
            }
        return true;
    }

    int checkBaBalanced(TreeNode* root){
        if (!root) return 0;
        int leftheight = checkBaBalanced(root->left);
        int rightheight = checkBaBalanced(root->right);
        if (leftheight == -1 || rightheight == -1) return -1;
        if(abs(leftheight - rightheight) > 1) return -1;
        return max(rightheight, leftheight) + 1;
    }
};