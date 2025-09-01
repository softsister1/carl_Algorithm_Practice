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
#include<iostream>
#include<vector>
#include<queue>
#include<tree>
 class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> result;
        if (!root) return result;
        queue<TreeNode*> qu;
        qu.push(root);
        while (!qu.empty()){
            vector<int> currentlevel;
            int levelnum = qu.size();
            for (int i = 0; i < levelnum; i++){
                TreeNode* node = qu.front();
                qu.pop();
                currentlevel.push_back(node->val);
                if(node->left) qu.push(node->left);
                if(node->right) qu.push(node->right);
            }
            result.push_back(currentlevel);
        }
        result.reverse(result.begin(),result.end());
        return result;
        
    }
};