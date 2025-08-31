/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/
#include<vector>

class Solution {
public:
    vector<vector<int>> levelOrder(Node* root) {
        vector<vector<int>> result;
        if (!root) return result;
        queue<Node*> qu;
        qu.push(root);
        while (!qu.empty()){
            int levelnum = qu.size();
            vector<int> currentlevel;
            for (int i = 0; i < levelnum; i++){
                Node* cur = qu.front();
                qu.pop();
                currentlevel.push_back(cur->val);
                for (Node* ch : cur->children){
                    if (ch) qu.push(ch);
                }
            }
            result.push_back(currentlevel);
        }
        return result;
    }
};