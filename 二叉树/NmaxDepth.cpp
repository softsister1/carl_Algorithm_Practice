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

class Solution {
public:
    int maxDepth(Node* root) {
    if (!root) return 0;
    
    int maxChild = 0;
    for (Node* child : root->children) {
        maxChild = max(maxChild, maxDepth(child));
    }
    
    return maxChild + 1;
}
};
