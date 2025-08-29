#include <queue>
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
        vector<vector<int>> levelOrder(TreeNode* root) {
            vector<vector<int>> result;
            if(!root) return result;
            queue<TreeNode*> q;
            q.push(root);
            while (!q.empty()){
                vector<int> currentLevel;
                int levelnum = q.size();
                for (int i = 0; i < levelnum; i++){
                    TreeNode* node = q.front();
                    currentLevel.push_back(node->val);
                    q.pop();
                    if (node->left) q.push(node->left);
                    if (node->right) q.push(node->right);

                }
                result.push_back(currentLevel);
            }
            return result;
        }

    };