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
    vector<int> goodSubsetofBinaryMatrix(vector<vector<int>> &grid)
    {
        int m = grid.size(), n = grid[0].size();
        vector<int> rows;
        vector<int> lookup(32, -1);
        for (auto i = 0; i < m; ++i)
        {
            int r = 0;
            for (auto j = 0; j < n; ++j)
                if (grid[i][j])
                    r |= 1 << j;
            if (lookup[r] == -1)
                lookup[r] = i;
            rows.push_back(r);
        }

        for (auto i = 0; i < m; ++i)
            for (auto j = 0; j < 32; ++j)
                if(lookup[j] != -1)
                {
                    auto mask = rows[i] | j;
                    if ((rows[i] ^ j) == mask)
                        if (i == lookup[j])
                            return {i};
                        else
                            return {i, lookup[j]};
                }

        return {};
    }
};

int main()
{
    Solution sol;
    vector<int> r;

    r = sol.goodSubsetofBinaryMatrix(vector<vector<int>>() = {{0, 1, 1, 0}, {0, 0, 0, 1}, {1, 1, 1, 1}});
    for (auto &c : r)
        cout << c << ", ";
    cout << endl;
}