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
    int countPyramids(vector<vector<int>> &grid)
    {
        int m = grid.size();
        int n = grid[0].size();

        vector<vector<int>> left(m, vector<int>(n));
        for (auto i = 0; i < m; ++i)
            for (auto j = 0; j < n; ++j)
                if (grid[i][j])
                {
                    auto t = i ? left[i - 1][j] : 0;
                    auto l = j ? left[i][j - 1] : 0;
                    auto tl = i && j ? left[i - 1][j - 1] : 0;
                    left[i][j] = min(min(t, l), tl + 1) + 1;
                }

        vector<vector<int>> right(m, vector<int>(n));
        for (auto i = 0; i < m; ++i)
            for (int j = n - 1; j >= 0; --j)
                if (grid[i][j])
                {
                    auto t = i ? right[i - 1][j] : 0;
                    auto r = j + 1 < n ? right[i][j + 1] : 0;
                    auto tr = i && (j + 1) < n ? right[i - 1][j + 1] : 0;
                    right[i][j] = min(min(t, r), tr + 1) + 1;
                }

        int rv = 0;
        for (auto i = 0; i < m; ++i)
            for (auto j = 0; j < n; ++j)
                if (min(left[i][j], right[i][j]))
                    rv += min(left[i][j], right[i][j]) - 1;

        vector<vector<int>> invleft(m, vector<int>(n));
        for (int i = m - 1; i >= 0; --i)
            for (auto j = 0; j < n; ++j)
                if (grid[i][j])
                {
                    auto b = i + 1 < m ? invleft[i + 1][j] : 0;
                    auto l = j ? invleft[i][j - 1] : 0;
                    auto bl = (i + 1) < m && j ? invleft[i + 1][j - 1] : 0;
                    invleft[i][j] = min(min(b, l), bl + 1) + 1;
                }

        vector<vector<int>> invright(m, vector<int>(n));
        for (int i = m - 1; i >= 0; --i)
            for (int j = n - 1; j >= 0; --j)
                if (grid[i][j])
                {
                    auto b = i + 1 < m ? invright[i + 1][j] : 0;
                    auto r = j + 1 < n ? invright[i][j + 1] : 0;
                    auto br = (i + 1) < m && (j + 1) < n ? invright[i + 1][j + 1] : 0;
                    invright[i][j] = min(min(b, r), br + 1) + 1;
                }

        for (auto i = 0; i < m; ++i)
            for (auto j = 0; j < n; ++j)
                if (min(invleft[i][j], invright[i][j]))
                    rv += min(invleft[i][j], invright[i][j]) - 1;

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.countPyramids(vector<vector<int>>() = {
                              {1, 1, 1, 1, 0},
                              {1, 1, 1, 1, 1},
                              {1, 1, 1, 1, 1},
                              {0, 1, 0, 0, 1}});
    cout << r << endl;

    // r = sol.countPyramids(vector<vector<int>>() = {{1, 1, 1}, {1, 1, 1}});
    // cout << r << endl;
}