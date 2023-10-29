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
    int dfs(vector<int> &coins, vector<vector<int>> &al, int k, int p, int u, int d)
    {
        if (dp[u][d] == 0)
        {
            int a = coins[u] / (1 << d) - k;
            int b = coins[u] / (1 << (d + 1));
            for (auto &v : al[u])
                if (v != p)
                    a += dfs(coins, al, k, u, v, d),
                        b += dfs(coins, al, k, u, v, min(19, d + 1));
            dp[u][d] = max(a, b) + 1;
        }

        return dp[u][d] - 1;
    }

    vector<vector<int>> dp;

public:
    int maximumPoints(vector<vector<int>> &edges, vector<int> &coins, int k)
    {
        int n = coins.size();
        vector<vector<int>> al(n);
        for (auto &e : edges)
            al[e[0]].push_back(e[1]),
                al[e[1]].push_back(e[0]);

        dp = vector<vector<int>>(n, vector<int>(20));
        return dfs(coins, al, k, -1, 0, 0);
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.maximumPoints(vector<vector<int>>() = {{1, 0}, {2, 1}, {3, 1}}, vector<int>() = {8, 2, 7, 1}, 2);
    cout << r << endl;

    r = sol.maximumPoints(vector<vector<int>>() = {{0, 1}, {0, 2}}, vector<int>() = {8, 4, 4}, 0);
    cout << r << endl;

    r = sol.maximumPoints(vector<vector<int>>() = {{0, 1}, {1, 2}, {2, 3}}, vector<int>() = {10, 10, 3, 3}, 5);
    cout << r << endl;
}