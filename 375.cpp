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

int dp[201][201] = {};
class Solution
{
    int dfs(int i, int j)
    {
        if (i >= j)
            return 0;

        int rv = 1e9;
        if (!dp[i][j])
        {
            for (auto k = i; k <= j; ++k)
                rv = min(rv, k + max(dfs(k + 1, j), dfs(i, k - 1)));
            dp[i][j] = rv + 1;
        }
        return dp[i][j] - 1;
    }

public:
    int getMoneyAmount(int n)
    {
        return dfs(1, n);
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.getMoneyAmount(10);
    cout << r << endl;
}