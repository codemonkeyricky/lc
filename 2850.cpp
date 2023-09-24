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
    int dfs(vector<vector<int>> &grid)
    {
        int ii, jj;
        bool done = 1;
        for (auto i = 0; i < 3 && done; ++i)
            for (auto j = 0; j < 3 && done; ++j)
                if (grid[i][j] > 1)
                    done = false, ii = i, jj = j;
        if (done)
            return 0;

        int rv = 1e9;
        for (int k = 0; k < 3; ++k)
            for (int l = 0; l < 3; ++l)
                if (grid[k][l] == 0)
                {
                    ++grid[k][l], --grid[ii][jj];
                    rv = min(rv, abs(k - ii) + abs(l - jj) + dfs(grid));
                    --grid[k][l], ++grid[ii][jj];
                }
        return rv;
    }

public:
    int minimumMoves(vector<vector<int>> &grid)
    {
        return dfs(grid);
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minimumMoves(vector<vector<int>>() = {{1, 1, 0}, {1, 1, 1}, {1, 2, 1}});
    cout << r << endl;
}