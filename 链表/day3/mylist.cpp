#include<iostream>

using namespace std;

class MyLinkedList{
private:
    struct ListNode{
        int val;
        ListNode *next;
        ListNode(int x): val(x),next(nullptr){

        };
    };

    ListNode *dummy;
    int size;

    ListNode *getindex(int index){
        if(index < 0||index >= size)
            return nullptr;

        ListNode *current = dummy->next;
        for(int i = 0; i < index; i++)
        {
            current = current->next;
        }
        return current;
    }

    ListNode *getPrevNode(int index) {
    if (index < 0 || index > size)  // 注意：这里是 > size，因为可以在末尾插入
        return nullptr;
        
    ListNode *current = dummy;

    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current;
    }

public:
    MyLinkedList(){
        dummy = new ListNode(0);
        size = 0;
    }
    ~MyLinkedList() {
        while (dummy != nullptr) {
            ListNode* temp = dummy;
            dummy = dummy->next;
            delete temp;
        }
    }
    int get(int index){
        ListNode *node = getindex(index);
        return node ? node->val : -1;
    }

    void addAtHead(int val) {
        ListNode* newNode = new ListNode(val);
        newNode->next = dummy->next;
        dummy->next = newNode;
        size++;
    }
    void addAtTail(int val) {
       
        addAtIndex(size, val);
    }
  
    void addAtIndex(int index, int val) {
        if (index > size) return;  // index太大，不插入
        if (index < 0) index = 0;  // index为负，插入到头部
        
        // ✅ 修正：找到index-1位置的节点
        ListNode *prev = getPrevNode(index);
        if (prev == nullptr) return;
        
        ListNode* newNode = new ListNode(val);
        newNode->next = prev->next;
        prev->next = newNode;
        size++;
    }
    
    // void deleteAtIndex(int index) {
    //     ListNode *node = getindex(index-1);
    //     node->next = node->next->next;
    //     size--;
    // }
    void deleteAtIndex(int index) {
        if (index < 0 || index >= size) return; 
        
        // ✅ 修正：找到要删除节点的前一个节点
        ListNode *prev = getPrevNode(index);
        if (prev == nullptr || prev->next == nullptr) return;
        
        ListNode *nodeToDelete = prev->next;  // ✅ 修正：保存要删除的节点
        prev->next = nodeToDelete->next;
        delete nodeToDelete;  // ✅ 修正：释放内存
        size--;
    }
    // 辅助函数：打印链表（用于调试）
    void printList() {
        cout << "链表: ";
        if (size == 0) {
            cout << "空";
        } else {
            ListNode* current = dummy->next;
            while (current != nullptr) {
                cout << current->val;
                if (current->next != nullptr) cout << " -> ";
                current = current->next;
            }
        }
        cout << " (长度: " << size << ")" << endl;
    }

    

};
// 测试代码
int main() {
    cout << "=== 测试 MyLinkedList ===" << endl;
    
    MyLinkedList* list = new MyLinkedList();
    
    cout << "1. 初始状态:" << endl;
    list->printList();
    
    cout << "\n2. addAtHead(1):" << endl;
    list->addAtHead(1);
    list->printList();
    
    cout << "\n3. addAtTail(3):" << endl;
    list->addAtTail(3);
    list->printList();
    
    cout << "\n4. addAtIndex(1, 2):" << endl;
    list->addAtIndex(1, 2);
    list->printList();
    
    cout << "\n5. get(1): " << list->get(1) << endl;
    
    cout << "\n6. deleteAtIndex(1):" << endl;
    list->deleteAtIndex(1);
    list->printList();
    
    cout << "\n7. get(1): " << list->get(1) << endl;
    
    delete list;  // 释放链表
    
    return 0;
}