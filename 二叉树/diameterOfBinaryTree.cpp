/*
*大疆26届嵌入式工程师笔试题
*2.给定一棵二叉树序列，返回该树的直径。二叉树的直径指树中任意两个节点之间最长路径的长度。这条路径可能经过也可能不经过根节点 root。
*两节点之间路径的长度由它们之间边数表示。序列定义:输入序列是二叉树的层序遍历，其从上到下、从左到右依次将节点值入队(包含空节点，但序列尾部空节点会被省略)，非空节点为非0值，空节点以0值表示。
*例：
* 
*表示为
*9
*120340005
*第一行为序列长度，第二行为层序遍历序列
*    1
*  /
*  2
* / \
*3   4
*     \
*      5
*/
#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
#include<string>

using namespace std;

struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr){
    }
};
class Solution{
public:
    int diameterOfBinaryTree(TreeNode* root) {
        Maxdiameter = 0;
        depth(root);
        return Maxdiameter;
    }
private:
    int Maxdiameter = 0;
    int depth(TreeNode* nodes){
        if (!nodes) return 0;
        int leftlen = depth(nodes->left);
        int rigthlen = depth(nodes->right);
        Maxdiameter = max(Maxdiameter, leftlen+rigthlen);
        return max(leftlen,rigthlen) + 1;
    }

};
vector<int> parse(string input){
    vector<int> result;
    for(char a : input){
        result.push_back(a - '0');
    }
    return result;
}




TreeNode* bulidtree(vector<int> nodes){
    if(nodes.size() == 0) return nullptr;
    queue<TreeNode*> qu;
    TreeNode* root = new TreeNode(nodes[0]);
    qu.push(root);
    int i = 1;
    while (!qu.empty() && i < nodes.size()){
       TreeNode* curr = qu.front();
       qu.pop();
       if (i < nodes.size()){
        if (nodes[i] != 0){
            curr->left = new TreeNode(nodes[i]);
            qu.push(curr->left);
        }
        i++;
       }
        if (i < nodes.size()){
        if (nodes[i] != 0){
            curr->right = new TreeNode(nodes[i]);
            qu.push(curr->right);
        }
        i++;
       } 
    }
    return root;
}
int main(){
    int lenth = 0;
    string input;
    cin >> lenth >> input;
    vector<int> nodes = parse(input);
    TreeNode* root = bulidtree(nodes);

    Solution su;
    int maxlen = su.diameterOfBinaryTree(root);
    cout << maxlen << endl;

    return 0;
}