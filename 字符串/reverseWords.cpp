#include <string>
    
class Solution {
public:
    string removespace(string s){
        int fast = 0;
        int slow = 0;
        while (fast < s.size()){
            if(s[fast] != ' '){
                s[slow] = s[fast];
                fast++;
                slow++;
            }
            else if( slow > 0 && s[slow - 1] != ' '){
                s[slow] = s[fast];
                fast++;
                slow++;
            }
            else{

                fast++;
            }
        }
            if (slow > 0 && s[slow - 1] == ' ') {
            slow--;  // 去掉末尾空格
            }
        return s;

    }
    void reverseString(string& s) {
        int left = 0;
        int right = s.size() - 1;
        while (left < right){
            int temp = s[left];
            s[left] = s[right];
            s[right] = temp;
            left++;
            right--;
        }
    }
    string reverseWords(string s) {
        s = removespace(s);
        reverseString(s);
        int right = 0;
        int left = 0; 
        for (int i = 0; i <= s.size(); i++){
            if(i == s.size() || s[i] == ' '){
                right = i - 1;
                while (left < right){
                int temp = s[left];
                s[left] = s[right];
                s[right] = temp;
                left++;
                right--;
                }
                left = i + 1;

            }
            
        }
        return s;


    }
};