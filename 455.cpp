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
    int findContentChildren(vector<int> &g, vector<int> &s)
    {
        sort(begin(g), end(g));
        sort(begin(s), end(s));
        int rv = 0;
        for (auto i = 0, j = 0; i < g.size() && j < s.size(); ++i, ++j)
        {
            while (j < s.size() && g[i] > s[j])
                ++j;
            if (j < s.size())
                ++rv;
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    // r = sol.findContentChildren(vector<int>() = {1, 2}, vector<int>() = {1, 2, 3});
    // cout << r << endl;

    r = sol.findContentChildren(vector<int>() = {1, 2, 3}, vector<int>() = {1, 1});
    cout << r << endl;
}