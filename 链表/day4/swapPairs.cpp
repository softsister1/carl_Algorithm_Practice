class Solution {
public:
struct ListNode {
        int val;
        ListNode *next;
        ListNode(int x) : val(x), next(nullptr) {}
    };
    ListNode* swapPairs(ListNode* head) {
        // 边界检查
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        
        ListNode *dummy = new ListNode(0);
        dummy->next = head;
        ListNode *prev = dummy;
        
        // 正确的循环条件：确保有两个节点可以交换
        while (prev->next != nullptr && prev->next->next != nullptr) {
            // 在循环内部重新定义first和second
            ListNode *first = prev->next;
            ListNode *second = prev->next->next;
            
            // 交换操作
            prev->next = second;
            first->next = second->next;
            second->next = first;
            
            // 更新prev指针，准备下一轮
            prev = first;
        }
        
        ListNode *newHead = dummy->next;
        delete dummy;
        return newHead;
    }
};