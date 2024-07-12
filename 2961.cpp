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
    vector<int> getGoodIndices(vector<vector<int>> &variables, int target)
    {
        vector<int> rv; 
        for (auto i = 0; i < variables.size(); ++i)
        {
            auto a = variables[i][0], b = variables[i][1], c = variables[i][2], m = variables[i][3];
            int aa = 1;
            for (auto k = 0; k < b; ++k)
                aa = (aa * a) % 10;

            a = aa;
            aa = 1;
            for (auto k = 0; k < c; ++k)
                aa = (aa * a) % m;

            if (aa == target)
                rv.push_back(i);
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    vector<int> r;

    // r = sol.getGoodIndices(vector<vector<int>>() = {{3, 3, 1, 3}}, 0);
    // for (auto &c : r)
    //     cout << c << ", ";
    // cout << endl;

    r = sol.getGoodIndices(vector<vector<int>>() = {{2, 3, 3, 10}, {3, 3, 3, 1}, {6, 1, 1, 4}}, 2);
    for (auto &c : r)
        cout << c << ", ";
    cout << endl;
}