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

class Solution {
  public:
    long long maximumTotalCost(vector<int>& nums) {
        int n = nums.size();
        vector<array<long long, 2>> dp(n); ///< [0] is odd index, [1] is even
        for (auto i = 0; i < n; ++i) {
            if (i == 0)
                dp[i] = {nums[0], nums[0]};
            else {
                ///<
                dp[i][0] = max(dp[i - 1][0], dp[i - 1][1]) + (long long)nums[i];
                dp[i][1] = dp[i - 1][0] + (long long)abs(nums[i]);
            }
        }
        return max(dp[n - 1][0], dp[n - 1][1]);
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.maximumTotalCost(vector<int>() = {-937});
    cout << r << endl;

    r = sol.maximumTotalCost(vector<int>() = {1, -1, 1, -1});
    cout << r << endl;

    r = sol.maximumTotalCost(vector<int>() = {1, -2, 3, 4});
    cout << r << endl;
}