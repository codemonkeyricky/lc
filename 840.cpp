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
    bool isMagic(vector<vector<int>> &grid, int i, int j)
    {
        auto s = grid[i][j] + grid[i + 1][j + 1] + grid[i + 2][j + 2];

        vector<int> uniq(10); 
        for (auto k = 0; k < 3; ++k)
            for (auto l = 0; l < 3; ++l)
            {
                if (grid[i + k][j + l] < 1 || grid[i + k][j + l] > 9)
                    return false;

                if (uniq[grid[i + k][j + l]])
                    return false;
                uniq[grid[i + k][j + l]] = true;
            }

        for (auto k = 0; k < 3; ++k)
        {
            int r = 0;
            for (auto l = 0; l < 3; ++l)
                r += grid[i + k][j + l];
            if (r != s)
                return false;
        }

        for (auto l = 0; l < 3; ++l)
        {
            int r = 0;
            for (auto k = 0; k < 3; ++k)
                r += grid[i + k][j + l];
            if (r != s)
                return false;
        }

        if (grid[i][j] + grid[i + 1][j + 1] + grid[i + 2][j + 2] != s)
            return false;

        if (grid[i + 2][j] + grid[i + 1][j + 1] + grid[i][j + 2] != s)
            return false;

        return true;
    }

public:
    int numMagicSquaresInside(vector<vector<int>> &grid)
    {
        int m = grid.size();
        int n = grid[0].size();
        int rv = 0;
        for (auto i = 0; i <= (m - 3); ++i)
            for (auto j = 0; j <= (n - 3); ++j)
                if (isMagic(grid, i, j))
                    ++rv;
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.numMagicSquaresInside(vector<vector<int>>() = {{4, 3, 8, 4}, {9, 5, 1, 9}, {2, 7, 6, 2}});
    cout << r << endl;

    r = sol.numMagicSquaresInside(vector<vector<int>>() = {{10, 3, 5}, {1, 6, 11}, {7, 9, 2}});
    cout << r << endl;
}