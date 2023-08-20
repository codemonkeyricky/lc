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
    int dfs(vector<vector<int>> &mat,
            vector<map<int, vector<array<int, 2>>>> &rows,
            vector<map<int, vector<array<int, 2>>>> &cols,
            array<int, 2> p)
    {
        int m = mat.size(), n = mat[0].size();
        int i = p[0], j = p[1], rv = 0;

        if (!dp[i * n + j])
        {
            auto vec = rows[i].upper_bound(mat[i][j]);
            if (vec != end(rows[i]))
                for (auto i = 0; i < vec->second.size(); ++i)
                    rv = max(rv, dfs(mat, rows, cols, vec->second[i]));

            vec = cols[j].upper_bound(mat[i][j]);
            if (vec != end(cols[j]))
                for (auto i = 0; i < vec->second.size(); ++i)
                    rv = max(rv, dfs(mat, rows, cols, vec->second[i]));
            dp[i * n + j] = 1 + rv;
        }
        return dp[i * n + j];
    }

    vector<int> dp;

public:
    int maxIncreasingCells(vector<vector<int>> &mat)
    {
        int m = mat.size(), n = mat[0].size();
        vector<map<int, vector<array<int, 2>>>> rows(m), cols(n);
        for (auto i = 0; i < m; ++i)
            for (auto j = 0; j < n; ++j)
                rows[i][mat[i][j]].push_back({i, j}),
                    cols[j][mat[i][j]].push_back({i, j});

        dp = vector<int>(m * n);

        int rv = 0;
        for (auto i = 0; i < m; ++i)
            for (auto j = 0; j < n; ++j)
                rv = max(rv, dfs(mat, rows, cols, {i, j}));

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.maxIncreasingCells(vector<vector<int>>() = {{-7}, {1}});
    cout << r << endl;

    r = sol.maxIncreasingCells(vector<vector<int>>() = {{7, 8}, {1, -8}});
    cout << r << endl;

    r = sol.maxIncreasingCells(vector<vector<int>>() = {{1, 1}, {1, 1}});
    cout << r << endl;

    r = sol.maxIncreasingCells(vector<vector<int>>() = {{3, 1}, {3, 4}});
    cout << r << endl;
}