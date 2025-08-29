class Solution {
    public:
        int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
            unordered_map<int, int> map1;
            for (int a : nums1){
                for (int b : nums2){
                    map1[a + b]++;
                }
            }
            int count = 0;
            for (int c : nums3){
                for (int d : nums4){
                    if (map1.count(0 - (c + d)) > 0){
                        count += map1[0 - (c + d)];
                    }
                }
            }
            return count;
        }

    };