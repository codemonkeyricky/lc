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
    long dfs(vector<vector<int>> &g, int i, int j, int k)
    {
        int m = g.size();
        int n = g[0].size();

        if (i < 0 || i >= m || j < 0 || j >= n)
            return 0;

        if (g[i][j] <= k)
            return 0;

        if (dp[i][j])
            return dp[i][j];

        vector<int> off = {0, -1, 0, 1, 0};
        long rv = 1;
        for (auto k = 0; k < 4; ++k)
            rv = (rv + dfs(g, i + off[k + 0], j + off[k + 1], g[i][j])) % 1000000007;
        rv2 = (rv2 + rv) % 1000000007;
        return dp[i][j] = rv;
    }

    int rv2 = 0;
    vector<vector<int>> dp;

public:
    int countPaths(vector<vector<int>> &grid)
    {
        int m = grid.size();
        int n = grid[0].size();

        rv2 = 0;
        dp = vector<vector<int>>(m, vector<int>(n));
        for (auto i = 0; i < m; ++i)
            for (auto j = 0; j < n; ++j)
                if (!dp[i][j])
                    dfs(grid, i, j, -1);
        return rv2;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.countPaths(vector<vector<int>>() = {{1, 2}});
    cout << r << endl;

    r = sol.countPaths(vector<vector<int>>() = {{1, 1}, {3, 4}});
    cout << r << endl;
}