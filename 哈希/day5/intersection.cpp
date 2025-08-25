// 349. 两个数组的交集

#include<vector>

class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> set1;
        for (int num : nums1){
            set1.insert(num);
        }
        unordered_set<int> resultSet;
        for (int num : nums2) {
            if (set1.find(num) != nullptr) {
                resultSet.insert(num);
            }
        }
        vector<int> result;
        for (int num : resultSet) {
        result.push_back(num);
    }
    return result;
    }
};
