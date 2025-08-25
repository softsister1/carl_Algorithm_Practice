class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.size() != t.size()) return false;
        int vector1[26] = {0};
        int vector2[26] = {0};
        int lenth = 0;
        for (char c : s){
            vector1[c - 'a']++;
        }
        for (char c : s){
            vector2[c - 'a']++;
        }

        for (int i = 0; i < 26; i++){
            if (vector1[i] != vector2[i]){
                return false;
            }
        }
        return true;
    }
};