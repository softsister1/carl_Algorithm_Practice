class Solution {
public:
    bool isHappy(int n) {
        unordered_set<int> seen;
        while (n != 1){
             if (seen.count(n) > 0) {
                return false;  // 进入循环
            }
            seen.insert(n);
            n = getSum(n);
        }
        return true;
        
    }
    int getSum(int n) {
        int sum = 0;
        while (n > 0) {
            int digit = n % 10;
            sum += digit * digit;
            n = n / 10;
        }
        return sum;
    }
};