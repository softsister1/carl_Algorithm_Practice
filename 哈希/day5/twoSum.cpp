#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        // 创建哈希表：数值 → 下标
        unordered_map<int, int> numToIndex;
        
        for (int i = 0; i < nums.size(); i++) {
            int complement = target - nums[i];
            
            if (numToIndex.count(complement) > 0) {
            return {numToIndex[complement], i};
        }
            
            // 将当前数字和下标存入哈希表
            numToIndex[i] = complement;
        }
        
        return {};  // 题目保证有答案，这行不会执行
    }
};