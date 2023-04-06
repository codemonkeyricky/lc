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
    vector<vector<int>> dp;

    int dfs(vector<vector<int>> &grid, vector<vector<int>> &cost, int i, int j)
    {
        int m = grid.size();
        int n = grid[0].size();

        if (i >= m - 1)
            return grid[i][j];

        if (!dp[i][j])
        {
            int rv = 1e9;
            for (auto l = 0; l < n; ++l)
                rv = min(rv, grid[i][j] + cost[grid[i][j]][l] + dfs(grid, cost, i + 1, l));
            dp[i][j] = rv + 1;
        }
        return dp[i][j] - 1;
    }

public:
    int minPathCost(vector<vector<int>> &grid, vector<vector<int>> &moveCost)
    {
        dp = vector<vector<int>>(51, vector<int>(51));
        int rv = 1e9;
        for (auto j = 0; j < grid[0].size(); ++j)
            rv = min(rv, dfs(grid, moveCost, 0, j));
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minPathCost(vector<vector<int>>() = {{5, 3}, {4, 0}, {2, 1}}, vector<vector<int>>() = {{9, 8}, {1, 5}, {10, 12}, {18, 6}, {2, 4}, {14, 3}});
    cout << r << endl;
}