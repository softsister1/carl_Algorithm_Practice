class Solution {
public:
    vector<int> getNext(string needle) {
    vector<int> next(needle.size(), 0);
    int j = 0; // 前缀末尾
    
    for (int i = 1; i < needle.size(); i++) { // 后缀末尾
        // 处理不匹配的情况
        while (j > 0 && needle[i] != needle[j]) {
            j = next[j - 1]; // 回退
        }
        
        // 匹配成功
        if (needle[i] == needle[j]) {
            j++;
        }
        
        next[i] = j;
    }
    return next;
}
    string longestPalindrome(string s) {
        
    }
};