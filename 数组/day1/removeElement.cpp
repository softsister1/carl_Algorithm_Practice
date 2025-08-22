#include<iostream>
#include <vector>

using namespace std;  

class Solution {
    public:
        int removeElement(vector<int>& nums, int val) {
            int A = 0;
            int B = 0;
            
            while(A < nums.size())
            {
                if(nums[A] != val)
                {
                    nums[B] = nums[A];
                    A++;
                    B++;
                }
                else
                {
                    A++;
                }
            }
            return  B ;
            
            
        }
    };