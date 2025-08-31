/*
给你一个整数数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧。
你只可以看到在滑动窗口内的 k 个数字。滑动窗口每次只向右移动一位。

返回 滑动窗口中的最大值 。

示例 1：

输入：nums = [1,3,-1,-3,5,3,6,7], k = 3
输出：[3,3,5,5,6,7]
解释：
滑动窗口的位置                最大值
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
示例 2：
输入：nums = [1], k = 1
输出：[1]

*/


#include <stack>
#include <iostream>
#include <deque>

using namespace std;

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> qu;
        vector<int> result;
        
        for (int i = 0; i < nums.size(); i++){
            // for (int j = i; j < k; j++){
            //     qu.push(num[j]);    

            // }
            while (!qu.empty() && nums[qu.back()] <= nums[i]){
                qu.pop_back();
            }
            qu.push_back(i)
            if(qu.front() <= (i-k)){
                qu.pop_front();
            }
            if (i >= k - 1){
                result.push_back(nums[qu.front()])
            }
            
        }
        return result;
    }
};