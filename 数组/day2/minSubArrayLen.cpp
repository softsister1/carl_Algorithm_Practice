#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int left = 0;
        int minLength = INT_MAX;  // 初始化为最大值
        int sum = 0;
        
        for (int right = 0; right < nums.size(); right++) {
            // 扩大窗口：加入right指向的元素
            sum += nums[right];
            
            // 当窗口和满足条件时，尝试缩小窗口
            while (sum >= target) {
                // 更新最小长度
                minLength = min(minLength, right - left + 1);
                // 缩小窗口：移除left指向的元素
                sum -= nums[left];
                left++;
            }
        }
        
        // 如果没找到满足条件的子数组，返回0
        return minLength == INT_MAX ? 0 : minLength;
    }
};

int main() {
    Solution solution;
    
    // 测试用例1
    vector<int> nums1 = {2,3,1,2,4,3};
    int target1 = 7;
    cout << "测试1: " << solution.minSubArrayLen(target1, nums1) << endl;  // 输出: 2
    
    // 测试用例2  
    vector<int> nums2 = {1,4,4};
    int target2 = 4;
    cout << "测试2: " << solution.minSubArrayLen(target2, nums2) << endl;  // 输出: 1
    
    // 测试用例3
    vector<int> nums3 = {1,1,1,1,1,1,1,1};
    int target3 = 11;
    cout << "测试3: " << solution.minSubArrayLen(target3, nums3) << endl;  // 输出: 0
    
    // 问题测试用例
    vector<int> nums4 = {1,2,3,4,5};
    int target4 = 15;
    cout << "测试4: " << solution.minSubArrayLen(target4, nums4) << endl;  // 输出: 5
    
    return 0;
}

/*
算法分析：
时间复杂度：O(n) - 每个元素最多被访问两次（一次right，一次left）
空间复杂度：O(1) - 只使用了几个变量

滑动窗口核心思想：
1. 用right指针扩大窗口，直到窗口和 >= target
2. 用left指针缩小窗口，寻找最小长度
3. 重复以上过程，直到right遍历完整个数组

关键优化：
- 避免重复计算窗口和，用sum变量维护
- 用while循环尽可能缩小窗口，找到所有可能的最小长度
*/