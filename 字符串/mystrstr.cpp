#include <string>

class Solution {
public:
    int strStr(string haystack, string needle) {
        for ( int i = 0; i < haystack.size(); i++){
            int temp = 0;
            if (haystack[i] == needle[0]){
                for (int j = 0; j < needle.size(); j++){
                    if( i + j > haystack.size()){
                        break;
                    }
                    if (haystack[i + j] == needle[j]){
                        temp++;
                    }
                }
                if (temp == needle.size())
                return i;
            }

        }
        return -1;
    }
};