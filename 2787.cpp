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
    int dp[301][301] = {};

    int dfs(int n, int k, vector<int> &powers)
    {
        if (n <= 0)
            return n == 0;

        if (k >= powers.size())
            return 0;

        if (!dp[n][k])
        {
            int rv = 0;
            rv = (rv + dfs(n, k + 1, powers)) % 1000000007;
            rv = (rv + dfs(n - powers[k], k + 1, powers)) % 1000000007;
            dp[n][k] = rv + 1;
        }
        return dp[n][k] - 1;
    }

public:
    int numberOfWays(int n, int x)
    {
        vector<int> powers;
        for (auto i = 1; pow(i, x) <= n; ++i)
            powers.push_back(pow(i, x));
        return dfs(n, 0, powers);
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.numberOfWays(83, 1);
    cout << r << endl;

    r = sol.numberOfWays(4, 1);
    cout << r << endl;

    r = sol.numberOfWays(10, 2);
    cout << r << endl;
}