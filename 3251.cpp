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
    int countOfPairs(vector<int>& nums) {
        int n = nums.size();

        const int N = 1001;
        const int M = 1001;
        const int MOD = 1000000007;

        array<array<int, M>, N> dp = {{}};
        for (auto k = 0; k <= nums[0]; ++k)
            dp[0][k] = 1;

        ///< pick a number c up to nums[i]
        ///< arr1: p <= c, arr2: nums[i - 1] - p >= c
        for (auto i = 1; i < n; ++i)
            for (auto c = 0; c <= nums[i]; ++c) {
                auto limit = min(nums[i - 1], c);
                for (int p = 0; p <= limit; ++p) {
                    if (c - p >= nums[i] - nums[i - 1])
                        dp[i][c] = (dp[i][c] + dp[i - 1][p]) % MOD;
                }
            }

        long rv = 0;
        for (auto it = begin(dp[nums.size() - 1]);
             it != end(dp[nums.size() - 1]); ++it)
            rv = (rv + *it) % MOD;

        return rv;
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.countOfPairs(vector<int>() = {5, 5, 5, 5});
    cout << r << endl;

    r = sol.countOfPairs(vector<int>() = {2, 3, 2});
    cout << r << endl;
}