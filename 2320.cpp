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
    const int MOD = 1000000007;
    int dp[10001][2][2] = {};
    int dfs(int n, int k = 0, int p1 = 0, int p2 = 0)
    {
        if (k >= n)
            return 1;

        if (!dp[k][p1][p2])
        {
            int rv = 0;
            if (p1 && p2)
                rv = dfs(n, k + 1, 0, 0) % MOD;
            else if (!p1 && p2)
                rv = (dfs(n, k + 1, 1, 0) + dfs(n, k + 1, 0, 0) )% MOD;
            else if (p1 && !p2)
                rv = (dfs(n, k + 1, 0, 0) + dfs(n, k + 1, 0, 1)) % MOD;
            else
            {
                rv = (rv + dfs(n, k + 1, 0, 0)) % MOD;
                rv = (rv + dfs(n, k + 1, 0, 1)) % MOD;
                rv = (rv + dfs(n, k + 1, 1, 0)) % MOD;
                rv = (rv + dfs(n, k + 1, 1, 1)) % MOD;
            }

            dp[k][p1][p2] = rv + 1;
        }
        return dp[k][p1][p2] - 1;
    }

public:
    int countHousePlacements(int n)
    {
        return dfs(n);
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}