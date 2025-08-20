#include<iostream>
#include<vector>

using namespace std;

class Solution {
    public:
        void rotate(vector<int>& nums, int k) {
            int n = nums.size();
            vector<int> results(n);
            for(int i = 0; i < n; i++)
            {
                results[(i+k)% n]=nums[i];
            }
            for(int i = 0; i < n; i++)
            {
                nums[i] = results[i];
            }

        }
    };