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
    void dfs(int n, int c, int k, vector<int> &rv)
    {
        if (!n)
        {
            rv.push_back(c);
            return;
        }

        if ((c % 10) + k < 10)
            dfs(n - 1, c * 10 + ((c % 10) + k), k, rv);
        if (k && (c % 10) - k >= 0)
            dfs(n - 1, c * 10 + ((c % 10) - k), k, rv);
    }

public:
    vector<int> numsSameConsecDiff(int n, int k)
    {
        vector<int> rv;
        for (auto i = 1; i < 10; ++i)
            dfs(n - 1, i, k, rv);
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    sol.numsSameConsecDiff(3, 7);
    cout << r << endl;
}