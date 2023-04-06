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
public:
    int goodBinaryStrings(int mmin, int mmax, int one, int zero)
    {
        long MOD = 1000000007;
        vector<array<long, 2>> dp(mmax + 1);
        dp[one][1] = dp[zero][0] = 1;
        for (auto i = 0; i < mmax + 1; ++i)
        {
            if (i - zero >= 0)
                dp[i][0] = (dp[i][0] + dp[i - zero][0] + dp[i - zero][1]) % MOD;

            if (i - one >= 0)
                dp[i][1] = (dp[i][1] + dp[i - one][0] + dp[i - one][1]) % MOD;
        }
        
        int rv = 0;
        for (auto i = mmin; i <= mmax; ++i)
            rv = (rv + dp[i][0] + dp[i][1]) % MOD;

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    // r = sol.goodBinaryStrings(4, 4, 4, 3);
    // cout << r << endl;

    r = sol.goodBinaryStrings(2, 3, 1, 2);
    cout << r << endl;
}