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
    int maxNonDecreasingLength(vector<int> &n0, vector<int> &n1)
    {
        int n = n0.size();
        vector<array<int, 2>> dp(n, {1, 1});
        dp[0][0] = dp[0][1] = 1;
        for (auto i = 1; i < n; ++i)
        {
            if (n0[i - 1] <= n0[i])
                dp[i][0] = max({dp[i - 1][0] + 1, dp[i][0], dp[i][0]});
            if (n1[i - 1] <= n0[i])
                dp[i][0] = max({dp[i - 1][1] + 1, dp[i][1], dp[i][0]});

            if (n1[i - 1] <= n1[i])
                dp[i][1] = max({dp[i - 1][1] + 1, dp[i][1], dp[i][1]});
            if (n0[i - 1] <= n1[i])
                dp[i][1] = max({dp[i - 1][0] + 1, dp[i][1], dp[i][1]});
        }

        int rv = 0;
        for (auto [a, b] : dp)
            rv = max({rv, a, b});
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.maxNonDecreasingLength(vector<int>() = {20, 13, 17}, vector<int>() = {10, 2, 12});
    cout << r << endl;

    r = sol.maxNonDecreasingLength(vector<int>() = {5, 16, 15}, vector<int>() = {12, 1, 14});
    cout << r << endl;

    r = sol.maxNonDecreasingLength(vector<int>() = {2, 3, 1}, vector<int>() = {1, 2, 1});
    cout << r << endl;
}