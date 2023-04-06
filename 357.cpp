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
    int dfs(int mask, int k, int n)
    {
        if (k >= n)
            return 1;

        int rv = 0;
        for (auto i = 0; i < 10; ++i)
            if (!(mask & (1 << i)))
                rv += dfs((i == 0 && !mask) ? 0 : (mask | (1 << i)), k + 1, n);
        return rv;
    }

public:
    int countNumbersWithUniqueDigits(int n)
    {
        return dfs(0, 0, n);
    }
};

int main()
{
    Solution sol;
    int r;

    // r = sol.countNumbersWithUniqueDigits(1);
    // cout << r << endl;

    r = sol.countNumbersWithUniqueDigits(2);
    cout << r << endl;
}