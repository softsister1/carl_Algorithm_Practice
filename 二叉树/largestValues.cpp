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
    vector<int> largestValues(TreeNode* root) {
        vector<int> result;
        if (!root) return result;
        queue<TreeNode*> qu;
        qu.push(root);
        while (!qu.empty()){
            int max = INT_MIN;
            int levelnum = qu.size();
            for (int i = 0; i < levelnum; i++){
                TreeNode* cur = qu.front();
                qu.pop();
                max = max > cur->val ? max : cur->val;
                if (cur->left) qu.push(cur->left);
                if (cur->right) qu.push(cur->right);
            }
            result.push_back(max);
        }
        return result;
    }
};