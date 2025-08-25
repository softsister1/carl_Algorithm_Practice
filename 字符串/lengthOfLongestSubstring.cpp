class Solution {
    public:
        int lengthOfLongestSubstring(string s) {
            int left = 0;
            int right = 0;
            int len = 0;
            int temp[128];
            for (int i = 0; i < 128; i++){
                temp[i] = -1;  
            }
            while (right < s.size()){
                int char1 = s[right];
                if (temp[char1] >= left){
                    left = temp[char1] + 1;
                }
                temp[char1] = right;
                len = max(len, right - left + 1);
                right++;
            }
            return len;
            
        }
    };