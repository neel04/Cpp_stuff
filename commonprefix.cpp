#include <vector>
#include <algorithm>
#include <iostream>

using std::cout;
using std::string;
using std::vector;

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        int idx = 0;
        bool cond = true;
        char cursor;
        string prefix = "";

        if (strs.size() == 0) return "";
        if (strs.size() == 1) return strs[0];

        while (cond){
            if (idx >= strs[0].size()) {
                break;
            }
            cursor = strs[0][idx];
        
            for (auto str : strs)
            {
                if (idx >= str.size() || str[idx] != cursor)
                {
                    cond = false;
                    break;
                }
            }
        
            if (cond) {
                prefix += cursor;
            }
            idx++;
        }

        return prefix;
    }
};

int main(){
    Solution solution;
    vector<string> strs = {"", ""};
    cout << solution.longestCommonPrefix(strs) << '\n';
    return 0;
}