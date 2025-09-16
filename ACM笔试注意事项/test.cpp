// ===== ACM模式重要注意事项 =====

// 1. 必备头文件模板
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
using namespace std;

// 2. 输入输出处理

// 常见输入格式：
// 格式1：多组数据，读到EOF
int a, b;
while (cin >> a >> b) {
    cout << a + b << endl;
}

// 格式2：先给组数
int t;
cin >> t;
while (t--) {
    // 处理每组数据
}

// 格式3：读取字符串并解析
string input;
cin >> input;
vector<int> nums;
for (char c : input) {
    nums.push_back(c - '0');  // 字符转数字
}

// 格式4：读取一行包含空格的数据
string line;
getline(cin, line);
istringstream iss(line);
int num;
while (iss >> num) {
    nums.push_back(num);
}

// 3. 常用数据结构声明

// 二叉树节点
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// 链表节点
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// 4. 常见算法模板

// BFS模板
queue<Node*> q;
q.push(start);
while (!q.empty()) {
    Node* curr = q.front();
    q.pop();
    // 处理当前节点
    // 加入相邻节点
}

// DFS递归模板
void dfs(Node* node) {
    if (!node) return;  // 边界条件
    // 处理当前节点
    dfs(node->left);    // 递归子问题
    dfs(node->right);
}

// 5. 调试技巧

// 本地测试时可以加入调试输出
#ifdef LOCAL
    cout << "Debug: " << variable << endl;
#endif

// 或者用条件编译
#define DEBUG 0
#if DEBUG
    cout << "Debug info" << endl;
#endif

// 6. 常见错误避免

// 错误1：忘记using namespace std
std::cout << "hello" << std::endl;  // 繁琐
cout << "hello" << endl;            // 简洁

// 错误2：数组越界
if (i < nums.size()) {  // 检查边界
    // 访问nums[i]
}

// 错误3：空指针访问
if (node) {  // 检查非空
    // 访问node->val
}

// 错误4：整数溢出
long long result = (long long)a * b;  // 防止溢出

// 错误5：函数声明顺序
// 要么把函数定义放在main之前
// 要么在使用前声明函数原型

// 7. 输出格式注意

// 每个结果单独一行
cout << result << endl;

// 多个数据一行，空格分隔
cout << a << " " << b << endl;

// 不要输出多余信息
cout << result << endl;        // ✓ 正确
cout << "答案是: " << result;  // ✗ 错误，多余信息

// 8. 内存管理（通常不需要，但了解一下）
TreeNode* root = new TreeNode(1);
// 在实际比赛中通常不需要delete，程序结束后自动释放

// 9. 时间复杂度估算
// n ≤ 10^4  → O(n^2) 可行
// n ≤ 10^5  → O(n log n) 可行  
// n ≤ 10^6  → O(n) 可行
// n ≤ 10^8  → O(log n) 可行

// 10. 常用STL容器和函数
vector<int> v;
v.push_back(x);          // 添加元素
v.size();                // 大小
v.empty();               // 是否为空

queue<int> q;
q.push(x);               // 入队
q.front();               // 队首
q.pop();                 // 出队

sort(v.begin(), v.end()); // 排序
reverse(v.begin(), v.end()); // 反转
max(a, b);               // 最大值
min(a, b);               // 最小值