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
    bool split(vector<int> &nums, int i, int j, int m)
    {
        if (i == j)
            return true;

        if (sum[j + 1] - sum[i] < m)
            return false;

        if (!dp[i][j])
        {
            int rv = 0;
            for (auto k = i; k < j && !rv; ++k)
                if (split(nums, i, k, m) && split(nums, k+1, j, m))
                    rv = true;
            dp[i][j] = rv + 1;
        }
        return dp[i][j] - 1;
    }

    vector<int> sum;
    vector<vector<int>> dp;

public:
    bool canSplitArray(vector<int> &nums, int m)
    {
        int n = nums.size();
        if (n <= 2)
            return true;
        dp = vector<vector<int>>(n, vector<int>(n));
        sum = vector<int>(n + 1);
        for (auto i = 0; i < n; ++i)
            sum[i + 1] = sum[i] + nums[i];
        return split(nums, 0, n - 1, m);
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.canSplitArray(vector<int>() = {2, 1, 3}, 5);
    cout << r << endl;

    r = sol.canSplitArray(vector<int>() = {2, 3, 3, 2, 3}, 6);
    cout << r << endl;
}