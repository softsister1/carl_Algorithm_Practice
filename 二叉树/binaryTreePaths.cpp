/*
给你一个二叉树的根节点 root ，按 任意顺序 ，返回所有从根节点到叶子节点的路径。

叶子节点 是指没有子节点的节点。

 
示例 1：


输入：root = [1,2,3,null,5]
输出：["1->2->5","1->3"]
示例 2：

输入：root = [1]
输出：["1"]
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
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> result;
        vector<int> path;
        DFS(root, path, result);
        return result;  

    }
    void DFS(TreeNode* curr, vector<int>& path, vector<string>& result){
        if(!curr) return;
        path.push_back(curr->val);
        if(!curr->left && !curr->right){
            result.push_back(pathtostring(path));
        }else{
            DFS(curr->left, path, result);
            DFS(curr->right, path, result);
        }
        
        path.pop_back();

    }
    string pathtostring(vector<int>& path){
        string result result = tostring(path[0]);
        for (int i = 0; i < path.size(); i++){
            result = "->" + tostring(path[i]);
        }
        return result;
    }

};