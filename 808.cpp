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
    map<array<int, 2>, array<long long, 3>> dp;

    array<long long, 3> dfs(int a, int b)
    {
        if (a <= 0 && b <= 0)
            return {1, 0, 0};

        if (a <= 0)
            return {0, 1, 0};

        if (b <= 0)
            return {0, 0, 1};

        if (!dp.count({a, b}))
        {
            auto r0 = dfs(a - 100, b - 0);
            auto r1 = dfs(a - 75, b - 25);
            auto r2 = dfs(a - 50, b - 50);
            auto r3 = dfs(a - 25, b - 75);
            dp[{a, b}] = {r0[0] + r1[0] + r2[0] + r3[0],
                          r0[1] + r1[1] + r2[1] + r3[1],
                          r0[2] + r1[2] + r2[2] + r3[2]};
        }

        return dp[{a, b}];
    }

public:
    double soupServings(int n)
    {
        dp.clear();
        auto r = dfs(n, n);
        return ((double)r[1] + (double)r[0] / 2) / (r[0] + r[1] + r[2]);
    }
};

int main()
{
    Solution sol;
    double r;

    // r = sol.soupServings(10000);
    // cout << r << endl;

    r = sol.soupServings(5000);
    cout << r << endl;

    r = sol.soupServings(1000);
    // cout << r << endl;

    r = sol.soupServings(100);
    cout << r << endl;

    r = sol.soupServings(50);
    cout << r << endl;
}