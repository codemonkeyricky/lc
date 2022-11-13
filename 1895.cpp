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
    int largestMagicSquare(vector<vector<int>> &grid)
    {
        int m = grid.size(), n = grid[0].size();
        for (int l = min(m, n); l >= 0; --l)
            for (auto i = 0; i < m - l + 1; ++i)
            {
                int valid = true;
                for (auto j = 0; j < n - l + 1; ++j, valid = true)
                {
                    auto sum = accumulate(begin(grid[i]) + j, begin(grid[i]) + j + l, 0);

                    for (auto x = 0, r = 0; x < l && valid; ++x, valid = (r == sum), r = 0)
                        for (auto y = 0; y < l; ++y)
                            r += grid[i + x][j + y];

                    for (auto x = 0, r = 0; x < l && valid; ++x, valid = (r == sum), r = 0)
                        for (auto y = 0; y < l; ++y)
                            r += grid[i + y][j + x];

                    int r, k;
                    for (k = 0, r = 0; k < l && valid; ++k)
                        r += grid[i + k][j + k];
                    valid = (r == sum);

                    for (k = 0, r = 0; k < l && valid; ++k)
                        r += grid[i + k][j + l - k - 1];
                    valid = (r == sum);

                    if (valid)
                        return l;
                }
            }

        return -1;
    }
};

int main()
{
    Solution sol;
    int r;

    // r = sol.largestMagicSquare(vector<vector<int>>() = {{1}});
    // cout << r << endl;

    r = sol.largestMagicSquare(vector<vector<int>>() = {{7, 1, 4, 5, 6}, {2, 5, 1, 6, 4}, {1, 5, 4, 3, 2}, {1, 2, 7, 3, 4}});
    cout << r << endl;
}