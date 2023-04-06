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
    int dfs(int i, int j, int k)
    {
        int n = importance.size();
        if (j >= n)
            if (i >= n)
                return 0;
            else 
                return importance[i][j-1] + k;

        if (!dp[i][j])
        {
            auto r0 = importance[i][j] + k + dfs(j + 1, j + 1, k);
            auto r1 = dfs(i, j + 1, k);
            dp[i][j] = min(r0, r1) + 1;
        }
        return dp[i][j] - 1;
    }

    vector<vector<int>> dp, importance; 

public:
    int minCost(vector<int> &nums, int k)
    {
        int n = nums.size(), rv = 1e9;
        importance = vector<vector<int>>(n, vector<int>(n));

        unordered_map<int, int> cnt;
        int uniq = 0;
        for (auto j = 0; j < n; ++j)
        {
            ++cnt[nums[j]];
            if (cnt[nums[j]] == 1)
                ++uniq;
            else if (cnt[nums[j]] == 2)
                --uniq;

            auto cnt_copy = cnt;
            int uniq_copy = uniq;
            for (auto i = 0; i <= j; ++i)
            {
                importance[i][j] = j - i + 1 - uniq_copy;
                --cnt_copy[nums[i]];
                if (cnt_copy[nums[i]] == 0)
                    --uniq_copy;
                else if (cnt_copy[nums[i]] == 1)
                    ++uniq_copy;
            }
        }

        dp = vector<vector<int>>(n, vector<int>(n, 0)); ///< k / split
        return dfs(0, 0, k);
    }
};

int main()
{
    Solution sol;
    int r;

    // r = sol.minCost(vector<int>() = {2, 3, 3, 3, 1, 5, 5, 0, 5, 3, 4, 2, 1, 2, 5, 1, 2, 0}, 5);
    // cout << r << endl;

    r = sol.minCost(vector<int>() = {1, 2, 1, 2, 1, 3, 3}, 2);
    cout << r << endl;
}