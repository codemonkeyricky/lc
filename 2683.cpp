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
    bool dfs(vector<int> &derived, vector<int> &orig, int k)
    {
        auto n = derived.size();
        if (k >= n)
            return orig[0] ^ orig[n - 1] == derived[n - 1];

        if (!dp[k])
        {
            orig[k] = 0;
            if (k == 0 || orig[k - 1] ^ orig[k] == derived[k - 1])
                if (dfs(derived, orig, k + 1))
                {
                    dp[k] = 2;
                    return true;
                }

            orig[k] = 1;
            if (k == 0 || orig[k - 1] ^ orig[k] == derived[k - 1])
                if (dfs(derived, orig, k + 1))
                {
                    dp[k] = 2;
                    return true;
                }
            
            dp[k] = 1;
        }

        return dp[k] - 1;
    }

    vector<int> dp;

public:
    bool doesValidArrayExist(vector<int> &derived)
    {
        int n = derived.size();
        dp = vector<int>(n);
        vector<int> orig(n);
        return dfs(derived, orig, 0);
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.doesValidArrayExist(vector<int>() = {1, 1, 0});
    cout << r << endl;
}