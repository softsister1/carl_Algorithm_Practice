/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
struct ListNode {
    int val;
    ListNode *next;
    
    // 构造函数
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode * dummy = new ListNode();
        dummy->next = head;
        ListNode *fast = dummy;

        ListNode *slow = dummy;
        for(int i = 0; i <= n; i++){
            fast = fast->next;
        }
        while(fast){
            fast = fast->next;
            slow = slow->next;
        }
        ListNode *temp = slow->next;
        slow->next = temp->next;
        delete temp;
        ListNode *newhead = dummy->next;
        delete dummy;
        return newhead;
    }
};


// class Solution {
// public:
//     ListNode* removeNthFromEnd(ListNode* head, int n) {
//         // 第一次反转
//         ListNode* reversed = reverseList(head);
        
//         // 删除第n个节点（现在变成正数第n个）
//         ListNode* dummy = new ListNode(0);
//         dummy->next = reversed;
//         ListNode* prev = dummy;
        
//         // 移动到要删除节点的前一个
//         for (int i = 0; i < n - 1; i++) {
//             prev = prev->next;
//         }
        
//         // 删除节点
//         if (prev->next != nullptr) {
//             ListNode* nodeToDelete = prev->next;
//             prev->next = prev->next->next;
//             delete nodeToDelete;
//         }
        
//         // 第二次反转，恢复原顺序
//         ListNode* result = reverseList(dummy->next);
//         delete dummy;
//         return result;
//     }
    
// private:
//     ListNode* reverseList(ListNode* head) {
//         ListNode* prev = nullptr;
//         ListNode* curr = head;
        
//         while (curr != nullptr) {
//             ListNode* temp = curr->next;
//             curr->next = prev;
//             prev = curr;
//             curr = temp;
//         }
        
//         return prev;
//     }
// };