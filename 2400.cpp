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
    int dfs(int n, int p, int k)
    {
        if (k == 0)
            return p == n;
        
        if(!dp[p + 2000][k])
            dp[p + 2000][k] = (dfs(n, p + 1, k - 1) + dfs(n, p - 1, k - 1)) % 1000000007 + 1;

        return dp[p + 2000][k] - 1;
    }

    int dp[4001][1001] = {};

public:
    int numberOfWays(int start, int end, int k)
    {
        return dfs(end, start, k);
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.numberOfWays(2, 5, 10);
    cout << r << endl;

    r = sol.numberOfWays(1, 2, 3);
    cout << r << endl;
}