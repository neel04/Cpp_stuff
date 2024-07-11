#include <iostream>
#include <string>
#include <algorithm>

using std::cout, std::endl, std::string;

class Solution
{
public:
    bool isPalindrome(int x)
    {
        string str_int = std::to_string(x);

        string rev_str = str_int;
        reverse(rev_str.begin(), rev_str.end());

        for (int i = 0; i < str_int.size(); i++)
        {
            if (str_int[i] != rev_str[i])
            {
                return false;
            }
        }

        return true;
    }
};

int main()
{
    int x = 1000021;
    Solution sol;
    cout << sol.isPalindrome(x) << endl;
}