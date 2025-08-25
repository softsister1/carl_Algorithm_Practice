#include <string>

class Solution {
public:
    string reverseStr(string s, int k) {
        int left = 0;
        int right = 0;
        int size = s.size();
        if (size < k){
            right = size - 1;
            while (left < right){
                int temp = s[left]; 
                s[left] = s[right];
                s[right] = temp;
                left++;
                right--;
                
            }
            return s;
        }
        for (int i = 0; i < size; i += 2*k){      
            left = i;
            right = left + k - 1;
            while (left < right){
                int temp = s[left]; 
                s[left] = s[right];
                s[right] = temp;
                left++;
                right--;
                
            }

            
        }
        return s;
    }
};