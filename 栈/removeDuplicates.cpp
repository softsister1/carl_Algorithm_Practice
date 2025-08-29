#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    string removeDuplicates(string s) {
        stack<char> st;
        for (char c : s){
            if (c != st.top()){
                st.push(c);
            }else{
                st.pop();
            }
        }
        string result = "";
        while (!st.empty()){
            result += st.top();
            st.pop();
        }
        reverse (result.begin(), result.end()); 
        return result;
        
        
    }
private:


};