/*


代码
测试用例
测试结果
测试结果
222. 完全二叉树的节点个数
简单
相关标签
premium lock icon
相关企业
给你一棵 完全二叉树 的根节点 root ，求出该树的节点个数。

完全二叉树 的定义如下：在完全二叉树中，除了最底层节点可能没填满外，其余每层节点数都达到最大值，并且最下面一层的节点都集中在该层最左边的若干位置。若最底层为第 h 层（从第 0 层开始），则该层包含 1~ 2h 个节点。

 

示例 1：


输入：root = [1,2,3,4,5,6]
输出：6
示例 2：

输入：root = []
输出：0
示例 3：

输入：root = [1]
输出：1
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
    int countNodes(TreeNode* root) {
        int numNodes;
        if (!root) return 0;
        queue<TreeNode*> qu;
        qu.push(root);
        while (!qu.empty()){
            int levelnum = qu.size();
            for (int i = 0; i < levelnum; i++){
                TreeNode* curr = qu.front();
                qu.pop();
                numNodes++;
                if (curr->left) qu.push(curr->left);
                if (curr->right) qu.push(curr->right);
            }
        }
        return numNodes;
    }
};