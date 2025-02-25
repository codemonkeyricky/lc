#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x), left(left), right(right) {}
};

TreeNode* recurse(vector<int>& tree, int k) {
    if (k >= tree.size() || tree[k] == -1)
        return nullptr;

    return new TreeNode(tree[k], recurse(tree, k * 2 + 1),
                        recurse(tree, k * 2 + 2));
}

TreeNode* populate(vector<int>& tree) { return recurse(tree, 0); }

void pvi(vector<int>& v) {

    for (auto& vv : v)
        cout << vv << ", ";
    cout << endl;
}

using vi = vector<int>;
using vvi = vector<vector<int>>;
using vll = vector<long long>;
using vvll = vector<vector<long long>>;

class Solution {
  public:
    // Helper function to check if a given maxDiff is feasible
    bool isValidDifference(vector<int> nums, int diff) {
        int n = nums.size();
        vector<int> lower, upper;

        // Traverse through the nums array
        for (int i = 0; i < n; i++) {
            // When an element is not -1 and is adjacent to a -1, compute
            // possible values
            if (nums[i] != -1 &&
                (i && nums[i - 1] == -1 ||
                 (i != nums.size() - 1) && nums[i + 1] == -1)) {

                /* min and max possible value for missing number */
                lower.push_back(nums[i] - diff);
                upper.push_back(nums[i] + diff);
            }
        }

        // Calculate the minimum and maximum values considering the allowed
        // difference
        int mmin = *min_element(lower.begin(), lower.end()) + 2 * diff;
        int mmax = *max_element(upper.begin(), upper.end()) - 2 * diff;

        // Now, for each -1 in the array, try to fill it with either `minValue`
        // or `maxValue`
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == -1) { // If it's a missing value
                // Try replacing with `minValue` first
                if ((i == 0 ||
                     abs(nums[i - 1] - mmin) <= diff) && // Check left neighbor
                    (i == (nums.size() - 1) || nums[i + 1] == -1 ||
                     abs(nums[i + 1] - mmin) <= diff)) // Check right neighbor
                {
                    nums[i] = mmin; // Replace with `minValue`
                } else {
                    nums[i] = mmax; // Otherwise, replace with `maxValue`
                }
            }
        }

        // After replacing all -1 values, check if the difference between
        // adjacent elements is within `maxDiff`
        for (int i = 0; i < nums.size() - 1; i++) {
            if (abs(nums[i] - nums[i + 1]) >
                diff) { // If any difference exceeds `maxDiff`, return false
                return false;
            }
        }

        // If no differences exceeded the allowed maxDiff, return true
        return true;
    }

    // Main function to find the minimum possible difference between adjacent
    // elements
    int minDifference(vector<int>& nums) {
        int missing = 0;

        for (int x : nums)
            if (x == -1)
                ++missing;

        if (missing == 0) {
            int diff = 0;
            for (int i = 0; i < nums.size() - 1; i++) {
                diff = max(
                    diff,
                    abs(nums[i] - nums[i + 1])); // Find the largest difference
            }
            return diff;
        } else if (missing == nums.size()) {

            return 0;
        }

        int l = 0;
        int r = 1000000005;

        while (l < r) {
            int m = (l + r) / 2; // Find the midpoint of the current range

            if (isValidDifference(nums, m)) {
                r = m; // If feasible, try a smaller `maxDiff`
            } else {
                l = m + 1; // If not feasible, try a larger `maxDiff`
            }
        }

        return l;
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.minDifference(vector<int>() = {14, -1, -1, 46});
    cout << r << endl;

    r = sol.minDifference(vector<int>() = {14, -1, -1, 46});
    cout << r << endl;

    r = sol.minDifference(vector<int>() = {-1, -1, 13, 34});
    cout << r << endl;

    r = sol.minDifference(vector<int>() = {1, 12});
    cout << r << endl;

    r = sol.minDifference(vector<int>() = {-1, 10, -1, 8});
    cout << r << endl;

    r = sol.minDifference(vector<int>() = {1, 2, -1, 10, 8});
    cout << r << endl;
}
