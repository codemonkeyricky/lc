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
    int dfs(vector<vector<int>> &grid, int i, int j, int v)
    {
        int m = grid.size(), n = grid[0].size();
        vector<int> D = {0, 1, 0, -1, 0};
        for (auto k = 0; k < 4; ++k)
        {
            int ni = i + D[k + 0];
            int nj = j + D[k + 1];
            if (ni >= 0 && ni < m && nj >= 0 && nj < n && grid[ni][nj] && vis[ni][nj] != v)
            {
                vis[ni][nj] = v;
                // found an augment path
                if (!match.count({ni, nj}) || dfs(grid, match[{ni, nj}][0], match[{ni, nj}][1], v))
                {
                    match[{ni, nj}] = {i, j};
                    match[{i, j}] = {ni, nj};
                    return 1;
                }
            }
        }
        return 0;
    }

    vector<vector<int>> vis;
    map<array<int, 2>, array<int, 2>> match;

public:
    int minimumOperations(vector<vector<int>> &grid)
    {
        int m = grid.size(), n = grid[0].size(), rv = 0;

        vis = vector<vector<int>>(m, vector<int>(n, -1));

        

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (grid[i][j] && !match.count({i, j}))
                    rv += dfs(grid, i, j, vis[i][j] = i * n + j);
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}