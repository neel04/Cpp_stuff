#include <vector>
#include <algorithm>
#include <iostream>

using std::sort;
using std::vector;
using std::distance;
using std::cout;

class Solution
{
public:
    int maxProfit(vector<int> &prices){
        int max_profit = 0;
        int min_price = prices[0];
        
        for (int price: prices){
            if (price < min_price){
                min_price = price;
            } else {
                max_profit = std::max(max_profit, price - min_price);
            }
        }

        return max_profit;
    }
};

int main()
{
    // Create an instance of the Solution class and test the maxProfit function
    Solution solution;
    vector<int> prices = {7, 1, 5, 3, 6, 4};
    std::cout << solution.maxProfit(prices) << '\n';

    vector<int> prices_2 = {2,1,2,0,1};
    std::cout << solution.maxProfit(prices_2) << '\n';
    return 0;
}