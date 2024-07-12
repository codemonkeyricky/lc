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
    int dfs(vector<int> &prices, int k, int free)
    {
        if (k >= prices.size())
            return 0;

        if (dp[k][free] == 0)
        {
            auto a = prices[k] + dfs(prices, k + 1, k + 1);
            int b = 1e9;
            if (free)
                b = dfs(prices, k + 1, free - 1);
            dp[k][free] = min(a, b) + 1;
        }
        return dp[k][free] - 1;
    }

    int dp[1001][1001] = {};

public:
    int minimumCoins(vector<int> &prices)
    {
        return dfs(prices, 0, 0);
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minimumCoins(vector<int>() = {3, 1, 2});
    cout << r << endl;
}