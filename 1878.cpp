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
    int rhombus(vector<vector<int>> &grid, int i, int j, int d)
    {
        if (d == 1)
            return grid[i][j];

        int m = grid.size();
        int n = grid[0].size();

        vector<int> off = {1, 1, -1, -1, 1};
        int sum = grid[i][j];
        for (auto k = 0, dd = d - 1, ni = i, nj = j; k < 4; ++k, dd = d - 1)
        {
            while (dd)
            {
                ni = ni + off[k + 0];
                nj = nj + off[k + 1];
                if (ni < 0 || ni >= m || nj < 0 || nj >= n)
                    return -1;
                if (!(ni == i && nj == j))
                    sum += grid[ni][nj];
                --dd;
            }
        }
        return sum;
    }

public:
    vector<int> getBiggestThree(vector<vector<int>> &grid)
    {
        set<int> rv; 
        int m = grid.size();
        int n = grid[0].size();
        for (auto i = 0; i < m; ++i)
            for (auto j = 0; j < n; ++j)
                for (auto k = 1, r = 0; k < 50 && r != -1; ++k)
                    if ((r = rhombus(grid, i, j, k)) != -1)
                        rv.insert(r);
        vector<int> rv2(begin(rv), end(rv));
        reverse(begin(rv2),end(rv2));
        if (rv2.size() <= 3)
            return rv2;
        else
            return {begin(rv2), begin(rv2) + 3};
    }
};

int main()
{
    Solution sol;
    int r;

    sol.getBiggestThree(vector<vector<int>>() = {{3, 4, 5, 1, 3}, {3, 3, 4, 2, 3}, {20, 30, 200, 40, 10}, {1, 5, 5, 4, 1}, {4, 3, 2, 2, 5}});
    cout << r << endl;
}