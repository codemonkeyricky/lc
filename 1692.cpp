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
    int dp[1001][1001] = {};
    int dfs(int n, int k, int empty)
    {
        if (n == 0 && empty == 0)
            return 1;

        if (n == 0)
            return 0;

        if (!dp[n][empty])
        {
            long long not_empty = k - empty, a = 0, b = 0;
            if (empty)
                a = dfs(n - 1, k, empty - 1);
            b = not_empty * dfs(n - 1, k, empty);
            dp[n][empty] = (a + b) % 1000000007 + 1;
        }
        return dp[n][empty] - 1;
    }

public:
    int waysToDistribute(int n, int k)
    {
        return dfs(n, k, k);
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.waysToDistribute(20, 5);
    cout << r << endl;

    r = sol.waysToDistribute(4, 2);
    cout << r << endl;

    r = sol.waysToDistribute(3, 2);
    cout << r << endl;
}