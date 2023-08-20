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
    int dfs(vector<int> &nums, int p, int mask)
    {
        int n = nums.size();
        if (mask == (1 << n) - 1)
            return 1;

        if (!dp[p][mask])
        {
            int rv = 0;
            for (auto i = 0; i < nums.size(); ++i)
                if ((1 << i) & ~mask)
                    if ((nums[p] % nums[i]) == 0 || (nums[i] % nums[p]) == 0)
                        rv = (rv + dfs(nums, i, mask | (1 << i))) % 1000000007;
            dp[p][mask] = rv;
        }
        return dp[p][mask];
    }

    vector<vector<int>> dp;

public:
    int specialPerm(vector<int> &nums)
    {
        int n = nums.size();
        dp = vector<vector<int>>(n, vector<int>(1 << n));
        int rv = 0;
        for (auto i = 0; i < n; ++i)
            rv = (rv + dfs(nums, i, 1 << i)) % 1000000007;
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.specialPerm(vector<int>() = {2, 3, 6});
    cout << r << endl;
}