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
    int minInsertions(string s)
    {
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n, 1e9));

        // base case
        for (auto i = 0; i < n; ++i)
            dp[i][i] = 0;

        for (auto i = 0; i < n - 1; ++i)
            if (s[i] == s[i + 1])
                dp[i][i + 1] = 0;
            else
                dp[i][i + 1] = 1;

        for (auto l = 2; l < n; ++l)
            for (auto i = 0; i < n - l; ++i)
                if (s[i] == s[i + l])
                    dp[i][i + l] = dp[i + 1][i + l - 1];
                else
                    dp[i][i + l] = min(dp[i][i + l - 1], dp[i + 1][i + l]) + 1;

        return dp[0][n - 1];
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minInsertions("mbadm");
    cout << r << endl;

    r = sol.minInsertions("zzazz");
    cout << r << endl;
}