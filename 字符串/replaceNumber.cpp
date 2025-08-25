#include <string>
using namespace std;

string replaceNumber(string s) {
    string result = "";
        
    for (int i = 0; i < s.size(); i++) {
        if (s[i] >= '0' && s[i] =< '9') {

            result += "number";
        } else {
            result += s[i];
        }
    }
    
    return result;
}