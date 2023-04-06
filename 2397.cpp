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
    int dfs(vector<int> &rows, int r, int mask, int cols)
    {
        mask |= rows[r];
        if (__builtin_popcount(mask) > cols)
            return -1e9; 
        
        int rv = 0;
        for (auto i = r + 1; i < rows.size(); ++i)
            rv = max(rv, dfs(rows, i, mask, cols));
        return rv + 1;
    }

public:
    int maximumRows(vector<vector<int>> &mat, int cols)
    {
        vector<int> rows(mat.size());
        for (auto i = 0; i < mat.size(); ++i)
            for (auto j = 0; j < mat[i].size(); ++j)
                if (mat[i][j])
                    rows[i] |= 1 << j;

        int rv = 0;
        for (auto i = 0; i < rows.size(); ++i)
            rv = max(rv, dfs(rows, i, 0, cols));

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.maximumRows(vector<vector<int>>() = {{1, 0, 1, 1, 1, 1}, {0, 0, 0, 1, 1, 0}, {1, 1, 0, 0, 0, 0}, {0, 0, 1, 1, 0, 1}}, 2);
    cout << r << endl;

    r = sol.maximumRows(vector<vector<int>>() = {{0, 0, 0}, {1, 0, 1}, {0, 1, 1}, {0, 0, 1}}, 2);
    cout << r << endl;
}