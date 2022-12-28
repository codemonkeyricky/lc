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
    using vi = vector<int>;
    using vvi = vector<vector<int>>;
    using vvvi = vector<vector<vector<int>>>;

    int dp[501][501][4] = {};

    int dfs(vector<vector<char>> &grid, int i, int j, int k)
    {
        int m = grid.size(), n = grid[0].size();
        if (i < 0 || i >= m || j < 0 || j >= n || grid[i][j] == 'W')
            return 0;

        if (!dp[i][j][k])
        {
            vector<int> offset = {0, 1, 0, -1, 0};
            int ni = i + offset[k + 0];
            int nj = j + offset[k + 1];
            dp[i][j][k] = (grid[i][j] == 'E') + dfs(grid, ni, nj, k);
            ++dp[i][j][k];
        }
        return dp[i][j][k] - 1;
    }

public:
    int maxKilledEnemies(vector<vector<char>> &grid)
    {
        // dp = vvvi(501, vvi(501, vi(4)));

        int rv = 0, m = grid.size(), n = grid[0].size();
        for (auto i = 0; i < m; ++i)
            for (auto j = 0; j < n; ++j)
                if (grid[i][j] == '0')
                {
                    int r = 0;
                    for (auto k = 0; k < 4; ++k)
                        r += dfs(grid, i, j, k);
                    rv = max(rv, r);
                }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}