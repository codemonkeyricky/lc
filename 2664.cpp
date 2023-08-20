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
    bool dfs(vector<vector<int>> &rv, int i, int j, int k = 0)
    {
        int m = rv.size(), n = rv[0].size();
        if (k >= m * n)
            return true;

        if (i >= 0 && i < m && j >= 0 && j < n && rv[i][j] == -1)
        {
            rv[i][j] = k;

            if (dfs(rv, i + 2, j + 1, k + 1))
                return true;

            if (dfs(rv, i + 2, j - 1, k + 1))
                return true;

            if (dfs(rv, i - 2, j + 1, k + 1))
                return true;

            if (dfs(rv, i - 2, j - 1, k + 1))
                return true;

            if (dfs(rv, i + 1, j + 2, k + 1))
                return true;

            if (dfs(rv, i + 1, j - 2, k + 1))
                return true;

            if (dfs(rv, i - 1, j + 2, k + 1))
                return true;

            if (dfs(rv, i - 1, j - 2, k + 1))
                return true;

            rv[i][j] = -1;
        }

        return false;
    }

public:
    vector<vector<int>> tourOfKnight(int m, int n, int r, int c)
    {
        vector<vector<int>> rv(m, vector<int>(n, -1));
        dfs(rv, r, c);
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    sol.tourOfKnight(1, 1, 0, 0);
}