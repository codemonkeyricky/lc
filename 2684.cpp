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
    int dfs(vector<vector<int>> &grid, int i, int j)
    {
        int m = grid.size(), n = grid[0].size();
        if (j == n - 1)
            return 0;

        if (!dp[i][j])
        {
            int rv = 0;

            if (i && grid[i][j] < grid[i - 1][j + 1])
                rv = max(rv, 1 + dfs(grid, i - 1, j + 1));

            if (grid[i][j] < grid[i][j + 1])
                rv = max(rv, 1 + dfs(grid, i, j + 1));

            if (i + 1 < m && grid[i][j] < grid[i + 1][j + 1])
                rv = max(rv, 1 + dfs(grid, i + 1, j + 1));

            dp[i][j] = rv + 1;
        }
        return dp[i][j] - 1;
    }

    vector<vector<int>> dp; 

public:
    int maxMoves(vector<vector<int>> &grid)
    {
        int m = grid.size(), n = grid[0].size();
        dp = vector<vector<int>>(m, vector<int>(n));
        int rv = -1e9;
        for (auto i = 0; i < m; ++i)
            rv = max(rv, dfs(grid, i, 0));
        return rv < 0 ? 0 : rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.maxMoves(vector<vector<int>>() = {{187, 167, 209, 251, 152, 236, 263, 128, 135},
                                              {267, 249, 251, 285, 73, 204, 70, 207, 74},
                                              {189, 159, 235, 66, 84, 89, 153, 111, 189},
                                              {120, 81, 210, 7, 2, 231, 92, 128, 218},
                                              {193, 131, 244, 293, 284, 175, 226, 205, 245}});
    cout << r << endl;
}