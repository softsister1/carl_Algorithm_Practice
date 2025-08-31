/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

class Solution {
public:
    Node* connect(Node* root) {
        queue<Node*> qu;
        qu.push(root);
        if (root != NULL) qu.push(root);
        while (!qu.empty()){
            int levelnum = qu.size();
            Node* preNode;
            Node* cur;
            for (int i = 0; i < levelnum; i++){
                if(i == 0){
                    preNode = qu.front();
                    qu.pop();
                    cur = preNode;
                }else{
                    cur = qu.front();
                    qu.pop();
                    preNode->next = cur;
                    preNode = cur;
                }
                if (cur->left) qu.push(cur->left);
                if (cur->right) qu.push(cur->right);
            }
            preNode->next = NULL;
        }
        return root;
    }
};