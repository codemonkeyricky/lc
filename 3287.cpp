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

    /*
     * dp[i][l]
     * subsequence ORs from 0... i with length n
     */

    __int128_t dfs(vector<int>& nums, int i, int l,
                   vector<vector<bool>>& solved, __int128_t dp[401][201]) {
        if (l == 0)
            return 0;

        if (i == -1)
            return 0;

        if (solved[i][l])
            return dp[i][l];

        /* recurrence */
        __int128_t rv = 0;
        if (l == 1)
            rv = (__int128_t)1 << nums[i];

        for (int ii = i - 1; ii >= 0; --ii) {
            /* including nums[i] */
            auto p = dfs(nums, ii, l - 1, solved, dp);
            __int128_t pp = 0;
            for (auto k = 0; k < 128; ++k) {
                if (((__int128_t)1 << k) & p) {
                    pp |= (__int128_t)1 << (k | nums[i]);
                }
            }
            rv |= pp;

            /* excluding nums[i] */
            pp = dfs(nums, ii, l, solved, dp);
            rv |= pp;
        }

        solved[i][l] = true;
        return dp[i][l] = rv;
    }

  public:
    int maxValue(vector<int>& nums, int k) {
        int n = nums.size();
        /*
         * i * l * l = 200 * 200 * 128
         */

        vector<vector<bool>> s1(n, vector<bool>(k + 1));
        __int128_t dp1[401][201] = {};
        dfs(nums, n - 1, k, s1, dp1);

        reverse(nums.begin(), nums.end());
        vector<vector<bool>> s2(n, vector<bool>(k + 1));
        __int128_t dp2[401][201] = {};
        dfs(nums, n - 1, k, s2, dp2);

        /* reverse again for debug */
        reverse(nums.begin(), nums.end());

        int rv = 0;
        for (auto i = 0; i < n - k; ++i) {
            __int128_t left = dp1[i][k];
            __int128_t right = dp2[n - i - 2][k];
            for (auto l = 0; l < 128; ++l)
                if (left & ((__int128_t)1 << l))
                    for (auto r = 0; r < 128; ++r)
                        if (right & ((__int128_t)1 << r))
                            rv = max(rv, l ^ r);
        }
        return rv;
    }
};

int main() {
    Solution sol;
    int r;

    cout << r << endl;
}
