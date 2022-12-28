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
public:
    vector<vector<int>> shiftGrid(vector<vector<int>> &grid, int k)
    {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> rv(m, vector<int>(n));
        for (auto i = 0; i < m; ++i)
            for (auto j = 0; j < n; ++j)
            {
                int offset = i * n + j + k;
                int ni = (offset / n) % m;
                int nj = (offset % n);
                rv[ni][nj] = grid[i][j];
            }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    sol.shiftGrid(vector<vector<int>>() = {{1}, {2}, {3}, {4}, {7}, {6}, {5}});
    cout << r << endl;
}