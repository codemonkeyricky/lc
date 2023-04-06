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
#include <cstring> 

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
    bool isThereAPath(vector<vector<int>> &grid)
    {
        int m = grid.size(), n = grid[0].size();

        if ((m + n - 1) % 2 == 1)
            return false;

        int max_ones = (m + n - 1) / 2;

        vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(max_ones + 2)));
        vector<int> empty(max_ones + 2);
        for (auto i = 0; i < m; ++i)
            for (auto j = 0; j < n; ++j)
            {
                if (i)
                    if (dp[i - 1][j] == empty)
                        dp[i][j][1] = grid[i][j];
                    else
                        for (auto k = 0; k < max_ones + 1; ++k)
                            dp[i][j][k + grid[i][j]] |= dp[i - 1][j][k];
                else
                    dp[i][j][1] |= grid[i][j];

                if (j)
                    if (dp[i][j - 1] == empty)
                        dp[i][j][1] |= grid[i][j];
                    else
                        for (auto k = 0; k < max_ones + 1; ++k)
                            dp[i][j][k + grid[i][j]] |= dp[i][j - 1][k];
                else
                    dp[i][j][1] |= grid[i][j];
            }

        return dp[m - 1][n - 1][max_ones];
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.isThereAPath(vector<vector<int>>() = {{0, 1, 0, 0}, {0, 1, 0, 0}, {1, 0, 1, 0}});
    cout << r << endl;
}