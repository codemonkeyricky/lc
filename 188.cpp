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
    using vvvi = vector<vector<vector<int>>>;
    using vvi = vector<vector<int>>;
    using vi = vector<int>;

public:
    int maxProfit(int k, vector<int> &prices)
    {
        int n = prices.size(); 

        if (n <= 0 || k <= 0)
            return 0;

        if (2 * k > n)
        {
            int rv = 0;
            for (int i = 1; i < n; i++)
                rv += max(0, prices[i] - prices[i - 1]);

            return rv;
        }

        // dp[i][used_k][ishold] = balance
        // ishold: 0 nothold, 1 hold
        vvvi dp(n, vvi(k + 1, vi(2, -1e9)));

        // set starting value
        dp[0][0][0] = 0;
        dp[0][1][1] = -prices[0];

        // fill the array
        for (int i = 1; i < n; i++)
            for (int j = 0; j <= k; j++)
            {
                // transition equation
                dp[i][j][0] = max(dp[i - 1][j][0], dp[i - 1][j][1] + prices[i]);
                if (j > 0)
                    dp[i][j][1] = max(dp[i - 1][j][1], dp[i - 1][j - 1][0] - prices[i]);
            }

        int rv = 0;
        for (int j = 0; j <= k; j++)
            rv = max(rv, dp[n - 1][j][0]);

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}