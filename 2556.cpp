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
    bool dfs(vector<vector<int>> &grid, int i, int j)
    {
        int m = grid.size(), n = grid[0].size();

        if (i == m - 1 && j == n - 1)
            return true;

        if (i >= grid.size() || j >= grid[0].size() || grid[i][j] == 0)
            return false;

        grid[i][j] = 0;
        return dfs(grid, i + 1, j) || dfs(grid, i, j + 1);
    }

    bool isPossibleToCutPath(vector<vector<int>> &grid)
    {
        if (dfs(grid, 0, 0) == false)
            return true;

        grid[0][0] = 1;

        return !dfs(grid, 0, 0);
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.isPossibleToCutPath(vector<vector<int>>() = {{1, 1, 1, 0, 0},
                                                         {1, 0, 1, 0, 0},
                                                         {1, 1, 1, 1, 1},
                                                         {0, 0, 1, 1, 1},
                                                         {0, 0, 1, 1, 1}});
    cout << r << endl;

    r = sol.isPossibleToCutPath(vector<vector<int>>() = {{1, 1}});
    cout << r << endl;

    r = sol.isPossibleToCutPath(vector<vector<int>>() = {{1, 1, 1}, {1, 0, 1}, {1, 1, 1}});
    cout << r << endl;
}