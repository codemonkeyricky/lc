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
    vector<vector<int>> colorRed(int n)
    {
        vector<vector<int>> rv;
        rv.push_back({1, 1});
        for (auto i = 2; i < n; ++i)
            rv.push_back({i, 1}), rv.push_back({i, i * 2 - 1});

        for (auto i = 1; i < n; i += 2)
            rv.push_back({n, i}), rv.push_back({n, n * 2 - i});

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}