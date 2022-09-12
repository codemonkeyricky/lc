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
    long long dp[1 << 17] = {};

    long long dfs(vector<int> &power, int mask)
    {
        int n = power.size();
        if (mask == ((1 << n) - 1))
            return 0;

        if (!dp[mask])
        {
            int gain = __builtin_popcount(mask) + 1;
            long long rv = 1e15;
            for (auto i = 0; i < n; ++i)
                if (!(mask & (1 << i)))
                    rv = min(rv, (power[i] + gain - 1) / gain + dfs(power, mask | 1 << i));
            dp[mask]  = rv;
        }
        return dp[mask];
    }

public:
    long long minimumTime(vector<int> &power)
    {
        return dfs(power, 0);
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minimumTime(vector<int>() = {1, 2, 4, 9});
    cout << r << endl;

    r = sol.minimumTime(vector<int>() = {1, 1, 4});
    cout << r << endl;

    r = sol.minimumTime(vector<int>() = {3, 1, 4});
    cout << r << endl;
}