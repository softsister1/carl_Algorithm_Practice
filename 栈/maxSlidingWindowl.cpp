class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> result;
        deque<int> dq;
        for (int i = 0; i < nums.size(); i++){
            while (!dq.empty() && nums[dq.back()] <= nums[i]){
                dq.pop_back();
            }
            dq.push(i);
            if (dq.front() <= (i - k)){
                dq.pop_front();
            }
            if (i >= k - 1){
                result.push_back(nums[dq.front()]);
            }
        }
        return result;
    }
};