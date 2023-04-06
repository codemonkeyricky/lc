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
    int dp[101][22] = {};
    int dfs(vector<vector<int>> &costs, int k, int p)
    {
        int m = costs.size();
        int n = costs[0].size();

        if (k >= m)
            return 0;

        if (!dp[k][p])
        {
            int rv = 1e9;
            for (auto i = 0; i < n; ++i)
                if (i != p)
                    rv = min(rv, costs[k][i] + dfs(costs, k + 1, i));
            dp[k][p] = rv + 1;
        }
        return dp[k][p] - 1;
    }

public:
    int minCostII(vector<vector<int>> &costs)
    {
        return dfs(costs, 0, 21);
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}