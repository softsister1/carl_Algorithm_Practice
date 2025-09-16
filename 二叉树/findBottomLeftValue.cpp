/*

代码
测试用例
测试结果
测试结果
513. 找树左下角的值
中等
相关标签
premium lock icon
相关企业
给定一个二叉树的 根节点 root，请找出该二叉树的 最底层 最左边 节点的值。

假设二叉树中至少有一个节点。

 

示例 1:



输入: root = [2,1,3]
输出: 1
示例 2:



输入: [1,2,3,4,null,5,6,null,null,7]
输出: */

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
    int findBottomLeftValue(TreeNode* root) {
        if (!root) return 0;
        queue<TreeNode*> qu;
        qu.push(root);
        int value = 0;
        while (!qu.empty()){
            int levelnum = qu.size();
            for (int i = 0; i < levelnum; i++){
                TreeNode* curr = qu.front();
                qu.pop();
                if (i == 0) value = curr->val;
                if (curr->left) qu.push(curr->left);
                if (curr->right) qu.push(curr->right);
            }

        }
        return value;
    }
};