#include<iostream>
#include <vector>

using namespace std;  

class Solution {
    public:
        vector<int> sortedSquares(vector<int>& nums) {
            int A = nums.size()-1;
            int B = 0;
            int pos = A;
            vector<int> results(nums.size());

            while(B <= A)
            {
                if(nums[A] * nums[A] >= nums[B] * nums[B])
                {
                    results[pos] = nums[A] * nums[A];
                    A--;
                }
                else
                {
                    results[pos] = nums[B] * nums[B];
                    B++;
                }
                pos--;
            }
            
            return results;
            
        }
    };