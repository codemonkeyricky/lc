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
    int minimumOperations(vector<vector<int>> &grid)
    {
        int m = grid.size(), n = grid[0].size();
        int r = 0;
        for (auto i = 0; i < m; ++i)
            for (auto j = 0; j < n; ++j)
                if ((i + j) % 2 == 0)
                    if (grid[i][j])
                        ++r;

        for (auto i = 0; i < m; ++i)
            for (auto j = 0; j < n; ++j)
                if ((i + j) % 2 == 0)
                    if (grid[i][j])
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}