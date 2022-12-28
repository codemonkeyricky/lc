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
    int projectionArea(vector<vector<int>> &grid)
    {
        int m = grid.size(), n = grid[0].size(), rv = 0;
        vector<int> rows(m), cols(n);
        for (auto i = 0; i < m; ++i)
            for (auto j = 0; j < n; ++j)
            {
                rows[i] = max(rows[i], grid[i][j]);
                cols[j] = max(cols[j], grid[i][j]);
                rv += !!grid[i][j];
            }
        rv += accumulate(begin(rows), end(rows), 0) + accumulate(begin(cols), end(cols), 0);
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}