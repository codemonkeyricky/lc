#include <iostream>
#include <vector>
#include <cassert>
#include <stack>
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <bitset>
#include <numeric>
#include <cmath>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

TreeNode *recurse(vector<int> &tree, int k)
{
    if (k >= tree.size() || tree[k] == -1)
        return nullptr;

    return new TreeNode(tree[k], recurse(tree, k * 2 + 1), recurse(tree, k * 2 + 2));
}

TreeNode *populate(vector<int> &tree)
{
    return recurse(tree, 0);
}

class Solution
{
public:
    int longestEqualSubarray(vector<int> &nums, int k)
    {
        int n = nums.size();
        map<int, vector<array<int, 2>>> dp;
        int rv = 1;
        for (auto i = 0; i < n; ++i)
        {
            if (dp[nums[i]].empty())
            {
                dp[nums[i]].push_back({0, i});
            }
            else
            {
                auto [mismatch, index] = dp[nums[i]].back();
                dp[nums[i]].push_back({mismatch + i - index - 1, i});

                auto &v = dp[nums[i]];
                array<int, 2> target = {v.back()[0] - k, 0};
                auto [mismatch_i, ii] = *lower_bound(begin(v), end(v), target);
                auto [mismatch_j, jj] = v.back();
                auto r = jj - ii + 1 - (mismatch_j - mismatch_i);
                rv = max(rv, r);
            }
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.longestEqualSubarray(vector<int>() = {1, 1, 2, 2, 1, 1}, 2);
    cout << r << endl;

    r = sol.longestEqualSubarray(vector<int>() = {1, 1, 2, 2, 1, 1}, 2);
    cout << r << endl;

    r = sol.longestEqualSubarray(vector<int>() = {1, 3, 2, 3, 1, 3}, 3);
    cout << r << endl;
}