class Solution {
    public:
        bool canConstruct(string ransomNote, string magazine) {
            int nums[26] = {0};
            for (char a : magazine){
                nums[a - 'a']++;
            }
            for (char a : ransomNote){
                if (nums[a - 'a'] == 0){
                    return false;
                }
                else{
                    nums[a - 'a']--;
                }
            }
            return true;

        }
    };