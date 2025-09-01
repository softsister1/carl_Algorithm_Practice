#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>

class Solution{
public:
    int diameterOfBinaryTree(TreeNode* root) {
        Maxdiameter = 0;
        depth(root);
        return Maxdiameter;
    };
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


struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr){
    }
}
vector<int> parse(string input){
    vector<int> result;
    for(char a : input){
        vector.push_back(a - '0');
    }
    return result;
}

TreeNode* bulidtree(vector<int> nodes){
    if(nodes.size() == 0) return nullptr;
    queue<TreeNode*> qu;
    TreeNode* root = new TreeNode(nodes[0]);
    qu.push(root);
    i = 1;
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