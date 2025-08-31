#include <deque>

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        unordered_map<int, int> map1;

        for (int num : nums){
            map1[num]++;
        }
        for (auto& [num, count] : map1){
            if (pq.size() < k){
                pq.push({count, num});
            }else if (count > pq.top().first){
                pq.pop();
                pq.push({count, num});
            }
        }
        vector<int> result; 
        while (!pq.empty()){
            result.push_back(pq.top().second);
            pq.pop();
        }
        return result;
    }

};