#include<queue>

/*
404. 左叶子之和
给定二叉树的根节点 root ，返回所有左叶子之和。

 

示例 1：



输入: root = [3,9,20,null,null,15,7] 
输出: 24 
解释: 在这个二叉树中，有两个左叶子，分别是 9 和 15，所以返回 24
示例 2:

输入: root = [1]
输出: 0
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

 struct TreeNode {
    int val;              // 节点值
    TreeNode* left;       // 左子树指针
    TreeNode* right;      // 右子树指针
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
class Solution {
public:
    int sumOfLeftLeaves(TreeNode* root) {
        if (!root) return 0;
        queue<TreeNode*> qu;
        qu.push(root);
        int sum = 0;
        while (!qu.empty()){
            TreeNode* curr = qu.front();
            qu.pop();
            if (curr->left){
                if (!curr->left->left && !curr->right->right){
                    sum += curr->left->val;
                }
                qu.push(curr->left);
            }
            if (curr->right){
                qu.push(curr->right);
            }
             
        }
        return sum;
    }
};