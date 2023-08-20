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
    int dfs(vector<int> &cost, vector<int> &time, int k, int remaining)
    {
        int n = cost.size();
        if (remaining <= 0)
            return 0;

        if (k >= n)
            return 1e9;

        if (!dp[k][remaining])
        {
            int rv = 0;
            int a = dfs(cost, time, k + 1, remaining);
            int b = cost[k] + dfs(cost, time, k + 1, remaining - 1 - time[k]);
            dp[k][remaining] = min(a, b) + 1;
        }
        return dp[k][remaining] - 1;
    }

    int dp[501][501] = {};

public:
    int paintWalls(vector<int> &cost, vector<int> &time)
    {
        return dfs(cost, time, 0, cost.size());
    }
};

int main()
{
    Solution sol;
    int r;

    // r = sol.paintWalls(vector<int>() = {76, 25, 96, 46, 85, 19, 29, 88, 2, 5}, vector<int>() = {1, 2, 1, 3, 1, 3, 3, 3, 2, 1});
    // cout << r << endl;

    // r = sol.paintWalls(vector<int>() = {26, 53, 10, 24, 25, 20, 63, 51}, vector<int>() = {1, 1, 1, 1, 2, 2, 2, 1});
    // cout << r << endl;

    // r = sol.paintWalls(vector<int>() = {2, 3, 4, 2}, vector<int>() = {1, 1, 1, 1});
    // cout << r << endl;

    r = sol.paintWalls(vector<int>() = {1, 2, 3, 2}, vector<int>() = {1, 2, 3, 2});
    cout << r << endl;
}