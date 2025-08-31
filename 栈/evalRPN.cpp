#include <stack>

class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> st;
        for (string& c : tokens){
            if (c == '+' || c == '-' || c == '*' || c == '/' ||){
                int b = st.top();
                st.pop();
                int a = st.pop();
                st.pop();
                int result;
                if (c == "+") {
                    result = a + b;
                } else if (c == "-") {
                    result = a - b;
                } else if (c == "*") {
                    result = a * b;
                } else {  
                    result = a / b;
                }
                st.push(result);
            }else{
                st.push(atoi(c));
            }
        }
        
    }
};