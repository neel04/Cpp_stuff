#include <iostream>
#include <string>
#include <stack>
#include <map>

using std::cout, std::endl, std::string, std::stack, std::map;

class Solution {
public:
    bool isValid(const string& s) {
        // Trivial case
        if (s.empty()) {
            return true;
        }

        // Initialize lookup table
        static const std::array<int, 128> lookup = []() {
            std::array<int, 128> arr{};
            arr['('] = ')';
            arr['['] = ']';
            arr['{'] = '}';
            return arr;
        }();

        stack<char> myStack;

        for (char chr : s) {
            // If stack is empty, push the character
            if (myStack.empty()) {
                myStack.push(chr);
                continue;
            }

            int topVal = myStack.top();

            // If we have a matching pair, pop the top element
            if (lookup[topVal] == chr) {
                myStack.pop();
            } else {
                // Otherwise, push the character
                myStack.push(chr);
            }
        }

        // Empty stack means all pairs were matched
        // Therefore, the string is valid
        return myStack.empty();
    }
};

int main() {
    Solution sol;
    string s = "{(})";
    cout << sol.isValid(s) << endl;
    return 0;
}