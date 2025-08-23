#include <iostream>
#include <vector>
#include <initializer_list>

using namespace std;

// 链表节点定义
struct ListNode {
    int val;
    ListNode *next;
    
    // 构造函数
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// 链表工具类
class LinkedListUtils {
public:
    // 方法1：从数组创建链表
    static ListNode* createFromArray(const vector<int>& arr) {
        if (arr.empty()) {
            return nullptr;
        }
        
        ListNode* head = new ListNode(arr[0]);
        ListNode* current = head;
        
        for (int i = 1; i < arr.size(); i++) {
            current->next = new ListNode(arr[i]);
            current = current->next;
        }
        
        return head;
    }
    
    // 方法2：从初始化列表创建链表（更方便）
    static ListNode* createFromList(initializer_list<int> values) {
        if (values.size() == 0) {
            return nullptr;
        }
        
        auto it = values.begin();
        ListNode* head = new ListNode(*it);
        ListNode* current = head;
        ++it;
        
        while (it != values.end()) {
            current->next = new ListNode(*it);
            current = current->next;
            ++it;
        }
        
        return head;
    }
    
    // 方法3：手动逐个添加节点
    static ListNode* createManually() {
        // 创建节点：1 -> 2 -> 6 -> 3 -> 4 -> 5 -> 6
        ListNode* head = new ListNode(1);
        head->next = new ListNode(2);
        head->next->next = new ListNode(6);
        head->next->next->next = new ListNode(3);
        head->next->next->next->next = new ListNode(4);
        head->next->next->next->next->next = new ListNode(5);
        head->next->next->next->next->next->next = new ListNode(6);
        
        return head;
    }
    
    // 打印链表
    static void printList(ListNode* head) {
        cout << "链表内容: ";
        if (head == nullptr) {
            cout << "空链表" << endl;
            return;
        }
        
        ListNode* current = head;
        while (current != nullptr) {
            cout << current->val;
            if (current->next != nullptr) {
                cout << " -> ";
            }
            current = current->next;
        }
        cout << " -> NULL" << endl;
    }
    
    // 计算链表长度
    static int getLength(ListNode* head) {
        int length = 0;
        ListNode* current = head;
        while (current != nullptr) {
            length++;
            current = current->next;
        }
        return length;
    }
    
    // 释放链表内存
    static void deleteList(ListNode* head) {
        while (head != nullptr) {
            ListNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
    
    // 在链表末尾添加节点
    static ListNode* appendNode(ListNode* head, int val) {
        ListNode* newNode = new ListNode(val);
        
        if (head == nullptr) {
            return newNode;
        }
        
        ListNode* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
        
        return head;
    }
    
    // 在链表头部添加节点
    static ListNode* prependNode(ListNode* head, int val) {
        ListNode* newNode = new ListNode(val);
        newNode->next = head;
        return newNode;
    }
};

// 解决方案类
class Solution {
public:
    // 方法1：使用虚拟头节点（推荐）
    ListNode* removeElements(ListNode* head, int val) {
        // 创建虚拟头节点
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        
        // 从虚拟头节点开始遍历
        ListNode* current = dummy;
        
        while (current->next != nullptr) {
            if (current->next->val == val) {
                // 删除节点
                ListNode* nodeToDelete = current->next;
                current->next = current->next->next;
                delete nodeToDelete;  // 释放内存
            } else {
                // 继续遍历
                current = current->next;
            }
        }
        
        // 保存真正的头节点
        ListNode* newHead = dummy->next;
        delete dummy;  // 释放虚拟头节点
        return newHead;
    }
    
    // 方法2：直接操作（不使用虚拟头节点）
    ListNode* removeElementsWithoutDummy(ListNode* head, int val) {
        // 处理头节点需要删除的情况
        while (head != nullptr && head->val == val) {
            ListNode* temp = head;
            head = head->next;
            delete temp;
        }
        
        // 如果链表全部被删除
        if (head == nullptr) {
            return nullptr;
        }
        
        // 处理中间节点
        ListNode* current = head;
        while (current->next != nullptr) {
            if (current->next->val == val) {
                ListNode* temp = current->next;
                current->next = current->next->next;
                delete temp;
            } else {
                current = current->next;
            }
        }
        
        return head;
    }
    
    // 方法3：递归解法（进阶）
    ListNode* removeElementsRecursive(ListNode* head, int val) {
        if (head == nullptr) {
            return nullptr;
        }
        
        // 递归处理后续节点
        head->next = removeElementsRecursive(head->next, val);
        
        // 判断当前节点是否需要删除
        if (head->val == val) {
            ListNode* temp = head;
            head = head->next;
            delete temp;
        }
        
        return head;
    }
};

// 测试函数
void testRemoveElements() {
    Solution solution;
    
    cout << "=== 测试删除链表元素 ===" << endl << endl;
    
    // 测试用例1：普通情况
    cout << "测试用例1：删除值为6的节点" << endl;
    ListNode* list1 = LinkedListUtils::createFromList({1, 2, 6, 3, 4, 5, 6});
    cout << "原始链表：";
    LinkedListUtils::printList(list1);
    
    ListNode* result1 = solution.removeElements(list1, 6);
    cout << "删除后：  ";
    LinkedListUtils::printList(result1);
    cout << "链表长度：" << LinkedListUtils::getLength(result1) << endl << endl;
    
    // 测试用例2：空链表
    cout << "测试用例2：空链表" << endl;
    ListNode* list2 = nullptr;
    cout << "原始链表：";
    LinkedListUtils::printList(list2);
    
    ListNode* result2 = solution.removeElements(list2, 1);
    cout << "删除后：  ";
    LinkedListUtils::printList(result2);
    cout << endl;
    
    // 测试用例3：所有节点都需要删除
    cout << "测试用例3：删除所有节点" << endl;
    ListNode* list3 = LinkedListUtils::createFromList({7, 7, 7, 7});
    cout << "原始链表：";
    LinkedListUtils::printList(list3);
    
    ListNode* result3 = solution.removeElements(list3, 7);
    cout << "删除后：  ";
    LinkedListUtils::printList(result3);
    cout << endl;
    
    // 测试用例4：头节点需要删除
    cout << "测试用例4：删除头节点" << endl;
    ListNode* list4 = LinkedListUtils::createFromList({6, 1, 2, 3});
    cout << "原始链表：";
    LinkedListUtils::printList(list4);
    
    ListNode* result4 = solution.removeElements(list4, 6);
    cout << "删除后：  ";
    LinkedListUtils::printList(result4);
    cout << endl;
    
    // 测试用例5：使用不同方法对比
    cout << "测试用例5：方法对比" << endl;
    vector<int> testData = {1, 2, 2, 1};
    
    ListNode* list5a = LinkedListUtils::createFromArray(testData);
    ListNode* list5b = LinkedListUtils::createFromArray(testData);
    ListNode* list5c = LinkedListUtils::createFromArray(testData);
    
    cout << "原始链表：";
    LinkedListUtils::printList(list5a);
    
    ListNode* result5a = solution.removeElements(list5a, 2);
    cout << "虚拟头节点法：";
    LinkedListUtils::printList(result5a);
    
    ListNode* result5b = solution.removeElementsWithoutDummy(list5b, 2);
    cout << "直接操作法：  ";
    LinkedListUtils::printList(result5b);
    
    ListNode* result5c = solution.removeElementsRecursive(list5c, 2);
    cout << "递归法：      ";
    LinkedListUtils::printList(result5c);
    
    // 清理内存
    LinkedListUtils::deleteList(result1);
    LinkedListUtils::deleteList(result2);
    LinkedListUtils::deleteList(result3);
    LinkedListUtils::deleteList(result4);
    LinkedListUtils::deleteList(result5a);
    LinkedListUtils::deleteList(result5b);
    LinkedListUtils::deleteList(result5c);
}

// 演示链表基础操作
void demonstrateLinkedListBasics() {
    cout << "=== 链表基础操作演示 ===" << endl << endl;
    
    // 1. 创建空链表
    cout << "1. 创建空链表：" << endl;
    ListNode* head = nullptr;
    LinkedListUtils::printList(head);
    cout << endl;
    
    // 2. 添加节点到头部
    cout << "2. 在头部添加节点 1, 2, 3：" << endl;
    head = LinkedListUtils::prependNode(head, 1);
    LinkedListUtils::printList(head);
    
    head = LinkedListUtils::prependNode(head, 2);
    LinkedListUtils::printList(head);
    
    head = LinkedListUtils::prependNode(head, 3);
    LinkedListUtils::printList(head);
    cout << endl;
    
    // 3. 添加节点到尾部
    cout << "3. 在尾部添加节点 4, 5：" << endl;
    head = LinkedListUtils::appendNode(head, 4);
    LinkedListUtils::printList(head);
    
    head = LinkedListUtils::appendNode(head, 5);
    LinkedListUtils::printList(head);
    cout << "链表长度：" << LinkedListUtils::getLength(head) << endl << endl;
    
    // 4. 从数组创建链表
    cout << "4. 从数组创建链表：" << endl;
    vector<int> arr = {10, 20, 30, 40, 50};
    ListNode* arrayList = LinkedListUtils::createFromArray(arr);
    LinkedListUtils::printList(arrayList);
    cout << endl;
    
    // 5. 从初始化列表创建链表
    cout << "5. 从初始化列表创建链表：" << endl;
    ListNode* initList = LinkedListUtils::createFromList({100, 200, 300});
    LinkedListUtils::printList(initList);
    cout << endl;
    
    // 清理内存
    LinkedListUtils::deleteList(head);
    LinkedListUtils::deleteList(arrayList);
    LinkedListUtils::deleteList(initList);
}

int main() {
    cout << "C++ 链表完整实现教程" << endl;
    cout << "========================" << endl << endl;
    
    // 演示链表基础操作
    demonstrateLinkedListBasics();
    
    cout << endl;
    
    // 测试删除元素功能
    testRemoveElements();
    
    cout << endl << "程序执行完毕！" << endl;
    
    return 0;
}

/*
学习要点：

1. 链表节点结构：
   - val: 存储数据
   - next: 指向下一个节点的指针
   - 构造函数: 初始化节点

2. 内存管理：
   - new: 分配内存
   - delete: 释放内存
   - 避免内存泄漏

3. 指针操作：
   - ->: 访问指针指向对象的成员
   - nullptr: 空指针
   - 指针赋值和移动

4. 链表基础操作：
   - 遍历: current = current->next
   - 插入: 修改指针指向
   - 删除: 跳过节点并释放内存

5. 边界情况处理：
   - 空链表
   - 单节点链表
   - 删除头节点
   - 删除所有节点
*/