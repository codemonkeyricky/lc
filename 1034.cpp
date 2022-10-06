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
    void dfs(vector<vector<int>> &g, int r, int c, int cl)
    {
        if (r < 0 || c < 0 || r >= g.size() || c >= g[r].size() || g[r][c] != cl)
            return;
        g[r][c] = -cl;
        dfs(g, r - 1, c, cl), dfs(g, r + 1, c, cl), dfs(g, r, c - 1, cl), dfs(g, r, c + 1, cl);
        if (r > 0 && r < g.size() - 1 && c > 0 && c < g[r].size() - 1 && cl == abs(g[r - 1][c]) &&
            cl == abs(g[r + 1][c]) && cl == abs(g[r][c - 1]) && cl == abs(g[r][c + 1]))
            g[r][c] = cl;
    }

public:
    vector<vector<int>> colorBorder(vector<vector<int>> &grid, int r0, int c0, int color)
    {
        dfs(grid, r0, c0, grid[r0][c0]);
        for (auto i = 0; i < grid.size(); ++i)
            for (auto j = 0; j < grid[i].size(); ++j)
                grid[i][j] = grid[i][j] < 0 ? color : grid[i][j];
        return grid;
    }
};

int main()
{
    Solution sol;
    int r;

    sol.colorBorder(vector<vector<int>>() = {{2, 1, 3, 2, 1, 1, 2},
                                             {1, 2, 3, 1, 2, 1, 2},
                                             {1, 2, 1, 2, 2, 2, 2},
                                             {2, 1, 2, 2, 2, 2, 2},
                                             {2, 3, 3, 3, 2, 1, 2}},
                    4, 4, 3);

    sol.colorBorder(vector<vector<int>>() = {{1, 2, 1, 2, 1, 2}, {2, 2, 2, 2, 1, 2}, {1, 2, 2, 2, 1, 2}}, 1, 3, 1);
    sol.colorBorder(vector<vector<int>>() = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}}, 1, 1, 2);
    sol.colorBorder(vector<vector<int>>() = {{1, 1}, {1, 2}}, 0, 0, 3);
}