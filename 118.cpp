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
    vector<vector<int>> generate(int rows)
    {
        vector<vector<int>> rv;
        rv.push_back({1});
        for (int i = 1; i < rows; ++i)
        {
            vector<int> row = {1};
            for (auto j = 0; j < rv.back().size() - 1; ++j)
                row.push_back(rv.back()[j] + rv.back()[j + 1]);
            row.push_back(1);
            rv.push_back(row);
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    sol.generate(5);
}