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
    int maxSum(vector<vector<int>> &grid)
    {
        int m = grid.size(), n = grid[0].size();
        vector<vector<long long>> mat(m, vector<long long>(n));

        for (auto i = 0; i < m; ++i)
            for (auto j = 0; j < n; ++j)
                mat[i][j] = grid[i][j] + (i ? mat[i - 1][j] : 0) + (j ? mat[i][j - 1] : 0) - (i && j ? mat[i - 1][j - 1] : 0);
        
        int rv = 0;
        for (auto i = 2; i < m; ++i)
            for (auto j = 2; j < n; ++j)
            {
                int r = mat[i][j] - (i - 3 >= 0 ? mat[i - 3][j] : 0) - (j - 3 >= 0 ? mat[i][j - 3] : 0) + (j - 3 >= 0 && i - 3 >= 0 ? mat[i - 3][j - 3] : 0);
                r -= grid[i - 1][j] + grid[i - 1][j - 2];
                rv = max(rv, r);
            }
        
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.maxSum(vector<vector<int>>() = {{6, 2, 1, 3}, {4, 2, 1, 5}, {9, 2, 8, 7}, {4, 1, 2, 9}});
    cout << r << endl;
}