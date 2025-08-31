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
#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    vector<double> averageOfLevels(TreeNode* root) {
        vector<double> result;
        if (!root) return result;
        queue<TreeNode*> qu;
        qu.push(root);

        while (!qu.empty()){
            double average;
            long sum = 0;
            int levelnum = qu.size();
            for (int i = 0; i < levelnum; i++){
                TreeNode* node = qu.front();
                qu.pop();
                sum += node->val;
                if(node->left) qu.push(node->left);
                if(node->right) qu.push(node->right);

            }
            result.push_back((double)sum / levelnum);        
        }
        return result;
    }
};