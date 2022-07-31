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
    int dfs(vector<vector<int>> &g1, vector<vector<int>> &g2, int i, int j)
    {
        int m = g1.size();
        int n = g1[0].size();
        if (i < 0 || j < 0 || i >= m || j >= n)
            return true;

        if (g2[i][j] == 2)
            return true;

        if (g1[i][j] == 0 && g2[i][j] == 1)
            return false;
        else if (g1[i][j] == 1 && g2[i][j] == 0)
            return true;
        else if (g1[i][j] == 0 && g2[i][j] == 0)
            return true;

        g2[i][j] = 2;
        vector<int> off = {0, -1, 0, 1, 0};
        for (auto k = 0; k < 4; ++k)
            if (!dfs(g1, g2, i + off[k], j + off[k + 1]))
                return false;
        return true;
    }

    void color(vector<vector<int>> &g, int i, int j)
    {
        int m = g.size();
        int n = g[0].size();
        if (i < 0 || j < 0 || i >= m || j >= n)
            return;

        if (g[i][j] == 1 || g[i][j] == 2)
        {
            g[i][j] = 3;
            vector<int> off = {0, -1, 0, 1, 0};
            for (auto k = 0; k < 4; ++k)
                color(g, i + off[k], j + off[k + 1]);
        }
    }

public:
    int countSubIslands(vector<vector<int>> &grid1, vector<vector<int>> &grid2)
    {
        int m = grid1.size();
        int n = grid1[0].size();

        int rv = 0;
        for (auto i = 0; i < m; ++i)
            for (auto j = 0; j < n; ++j)
                if (grid2[i][j] == 1)
                {
                    if (dfs(grid1, grid2, i, j))
                        ++rv;
                    color(grid2, i, j);
                }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.countSubIslands(vector<vector<int>>() = {{1, 1, 1, 1, 0, 0}, {1, 1, 0, 1, 0, 0}, {1, 0, 0, 1, 1, 1}, {1, 1, 1, 0, 0, 1}, {1, 1, 1, 1, 1, 0}, {1, 0, 1, 0, 1, 0}, {0, 1, 1, 1, 0, 1}, {1, 0, 0, 0, 1, 1}, {1, 0, 0, 0, 1, 0}, {1, 1, 1, 1, 1, 0}},
                            vector<vector<int>>() = {{1, 1, 1, 1, 0, 1}, {0, 0, 1, 0, 1, 0}, {1, 1, 1, 1, 1, 1}, {0, 1, 1, 1, 1, 1}, {1, 1, 1, 0, 1, 0}, {0, 1, 1, 1, 1, 1}, {1, 1, 0, 1, 1, 1}, {1, 0, 0, 1, 0, 1}, {1, 1, 1, 1, 1, 1}, {1, 0, 0, 1, 0, 0}});
    cout << r << endl;

    r = sol.countSubIslands(vector<vector<int>>() = {{1, 1, 1, 0, 0}, {0, 1, 1, 1, 1}, {0, 0, 0, 0, 0}, {1, 0, 0, 0, 0}, {1, 1, 0, 1, 1}},
                            vector<vector<int>>() = {{1, 1, 1, 0, 0}, {0, 0, 1, 1, 1}, {0, 1, 0, 0, 0}, {1, 0, 1, 1, 0}, {0, 1, 0, 1, 0}});
    cout << r << endl;
}