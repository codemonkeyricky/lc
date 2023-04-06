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
    vector<int> findBall(vector<vector<int>> &grid)
    {
        int m = grid.size(), n = grid[0].size();

        for (auto i = 0; i < m; ++i)
        {
            for (auto j = 1; j < n; ++j)
                if (grid[i][j - 1] == 1 && grid[i][j] == -1)
                    grid[i][j - 1] = grid[i][j] = 0;
            if (grid[i][0] == -1)
                grid[i][0] = 0;
            if (grid[i][n - 1] == 1)
                grid[i][n - 1] = 0;
        }

        vector<int> curr(n);
        for (auto i = 0; i < n; ++i)
            curr[i] = i;
        
        for (auto i = 0; i < m; ++i)
        {
            vector<int> next(n, -1);
            for (auto j = 0; j < n; ++j)
            {
                if (grid[i][j] && curr[j] != -1)
                {
                    if (grid[i][j] == 1)
                        next[j + 1] = curr[j];
                    else
                        next[j - 1] = curr[j];
                }
            }
            swap(curr, next);
        }

        vector<int> rv(n, -1);
        for (auto j = 0; j < n; ++j)
            if (curr[j] != -1)
                rv[curr[j]] = j;

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    sol.findBall(vector<vector<int>>() = {{1, 1, 1, -1, -1}, {1, 1, 1, -1, -1}, {-1, -1, -1, 1, 1}, {1, 1, 1, 1, -1}, {-1, -1, -1, -1, -1}});
}