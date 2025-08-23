class Solution {
public:
struct ListNode {
    int val;
    ListNode *next;
    
    // 构造函数
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
    ListNode* reverseList(ListNode* head) {
        ListNode *temp;
        ListNode *cur = head;
        ListNode *pre = nullptr;
        while(cur){
            temp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = temp;
            
        }
        
        return pre;
    }
};