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
    vector<int> parent;
    int m, n;

    int find(int k)
    {
        if (parent[k] < 0)
            return k;
        return parent[k] = find(parent[k]);
    }

    void combine(int i, int j, int k, int l)
    {
        if (i >= m || j >= n)
            return;

        auto p1 = find(i * n + j);
        auto p2 = find(k * n + l);
        if (p1 != p2)
        {
            if (parent[p2] < parent[p1])
                swap(p1, p2);
            parent[p1] += parent[p2];
            parent[p2] = p1;
        }
    }

public:
    int findMaxFish(vector<vector<int>> &grid)
    {
        m = grid.size(), n = grid[0].size();
        parent = vector<int>(m * n);

        for (auto i = 0; i < m; ++i)
            for (auto j = 0; j < n; ++j)
                parent[i * n + j] = -grid[i][j];

        for (auto i = 0; i < m; ++i)
            for (auto j = 0; j < n; ++j)
                if (grid[i][j])
                {
                    if (i + 1 < m && grid[i + 1][j])
                        combine(i, j, i + 1, j);

                    if (j + 1 < n && grid[i][j + 1])
                        combine(i, j, i, j + 1);
                }

        int rv = 0;
        for (auto i = 0; i < m; ++i)
            for (auto j = 0; j < n; ++j)
                if (grid[i][j])
                    rv = max(rv, -parent[find(i * n + j)]);

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.findMaxFish(vector<vector<int>>() = {{0}, {0}});
    cout << r << endl;

    r = sol.findMaxFish(vector<vector<int>>() = {{0, 2, 1, 0}, {4, 0, 0, 3}, {1, 0, 0, 4}, {0, 3, 2, 0}});
    cout << r << endl;
}