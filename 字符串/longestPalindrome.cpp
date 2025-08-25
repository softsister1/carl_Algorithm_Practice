#include<string>

class Solution {
    public:
    string longestPalindrome(string s) {
        if (s.empty()) return "";
        
        int start = 0;  // 最长回文的起始位置
        int maxLen = 1; // 最长回文的长度
        
        for (int i = 0; i < s.size(); i++) {
            // 情况1：以 i 为中心的奇数长度回文
            int len1 = expandAroundCenter(s, i, i);
            
            // 情况2：以 i 和 i+1 为中心的偶数长度回文  
            int len2 = expandAroundCenter(s, i, i + 1);
            
            // 更新最长回文信息
            int currentMaxLen = max(len1, len2);
            if (currentMaxLen > maxLen) {
                maxLen = currentMaxLen;
                start = i - (currentMaxLen - 1) / 2;  // 计算起始位置
            }
        }
        return s.substr(start, maxLen);
    }
    int expandAroundCenter(string s, int left, int right){
        while (left >= 0 && right < s.size() && s[left] == s[right]) {
            left--;
            right++;
        }
        return right - left - 1;
    }

    };