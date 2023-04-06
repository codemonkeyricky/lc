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
    int dp[2001][2001] = {};
    bool isPalindrome(int i, int j)
    {
        if (i == j)
            return true;

        auto l = j - i + 1;
        if (l % 2)
            return dp[i][i + l / 2 - 1] == dp[j][i + l / 2 + 1];
        else
            return dp[i][i + l / 2 - 1] == dp[j][i + l / 2];
    }

public:
    int maxPalindromes(string s, int k)
    {
        if (k == 1)
            return s.size();

        int n = s.size();
        for (long i = 0, hash = 0; i < n; ++i, hash = 0) 
            for (int j = i; j < n; ++j)
                hash = (hash * 26 + s[j] - 'a') % 1000000009, dp[i][j] = hash;

        for (long i = n - 1, hash = 0; i >= 0; --i, hash = 0)
            for (int j = i; j >= 0; --j)
                hash = (hash * 26 + s[j] - 'a') % 1000000009, dp[i][j] = hash;

        int rv = 0;
        vector<int> dp2(n);
        for (int j = k - 1; j < n; ++j)
        {
            dp2[j] = max((j ? dp2[j - 1] : 0), (int)isPalindrome(0, j));
            for (auto i = 0; i + k <= j; ++i)
                dp2[j] = max(dp2[j], dp2[i] + isPalindrome(i + 1, j));
        }

        return dp2[n-1];
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.maxPalindromes("sjbxiufnaanqkwsqswkqrcznzcddhtuhtthuttjfuufjtcfywgecegwyhhnnhtozczirynhhnyrire", 3);
    cout << r << endl;

    // r = sol.maxPalindromes("iqqibcecvrbxxj", 1);
    // cout << r << endl;

    r = sol.maxPalindromes("kwnwkekokedadq", 5);
    cout << r << endl;

    r = sol.maxPalindromes("adbcda", 2);
    cout << r << endl;

    r = sol.maxPalindromes("abaccdbbd", 3);
    cout << r << endl;
}