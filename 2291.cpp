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
    vector<vector<int>> dp;
    int dfs(vector<int> &cost, vector<int> &profit, int k, int b)
    {
        int n = cost.size();
        if (k >= n)
            return 0;

        if (!dp[k][b])
        {
            int r0 = dfs(cost, profit, k + 1, b);
            int r1 = 0;
            if (b >= cost[k])
                r1 = profit[k] + dfs(cost, profit, k + 1, b - cost[k]);

            dp[k][b] = max(r0, r1) + 1;
        }
        return dp[k][b] - 1;
    }

public:
    int maximumProfit(vector<int> &present, vector<int> &future, int budget)
    {
        int n = present.size();
        dp = vector<vector<int>>(1001, vector<int>(1001));
        vector<int> profit(n);
        for (auto i = 0; i < n; ++i)
            profit[i] = max(profit[i], future[i] - present[i]);

        return dfs(present, profit, 0, budget);
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.maximumProfit(vector<int>() = {0, 0, 0, 1, 3}, vector<int>() = {3, 3, 4, 4, 2}, 10);
    cout << r << endl;

    r = sol.maximumProfit(vector<int>() = {5, 4, 6, 2, 3}, vector<int>() = {8, 5, 4, 3, 5}, 10);
    cout << r << endl;
}