#include <iostream>
#include <vector>
#include <unordered_map>

using std::vector, std::cout, std::endl, std::sort, std::unordered_map;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> hashmap;

        for (size_t i = 0; i < nums.size(); i++){
            int complement = target - nums[i];
            hashmap[complement] = static_cast<int>(i);

            if (hashmap.size() != 1 && hashmap.find(nums[i]) != hashmap.end()){
                return {hashmap[nums[i]], static_cast<int>(i)};
            }

        }

        return {};
    }
};

int main() {
    vector<int> nums = {3, 3};
    vector<int> result = Solution().twoSum(nums, 6);
    
    // Print the result
    cout << "Indices: " << result[0] << ", " << result[1] << endl;
    
    return 0;
}
