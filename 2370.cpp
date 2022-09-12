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
    int dfs(string &s, int k, int i, vector<vector<int>> &jump, vector<int> &dp)
    {
        if (i >= s.size() - 1)
            return 0;

        if (!dp[i])
        {
            int rv = 0;
            for (auto j = 0; j < 26; ++j)
                if (abs(j - (s[i] - 'a')) <= k)
                    if (jump[i + 1][j] != -1 && jump[i + 1][j] != i)
                        rv = max(rv, dfs(s, k, jump[i + 1][j], jump, dp) + 1);
            dp[i] = rv + 1; 
        }
        return dp[i] - 1;
    }

public:
    int longestIdealString(string s, int k)
    {
        int n = s.size();
        vector<vector<int>> jump(n, vector<int>(26, -1));
        for (int i = n - 1; i >= 0; --i)
        {
            if (i < n - 1)
                jump[i] = jump[i + 1];
            jump[i][s[i] - 'a'] = i;
        }

        int rv = 0;
        vector<int> dp(n);
        for (auto i = 0; i < s.size(); ++i)
            rv = max(rv,  dfs(s, k, i, jump, dp));
        return rv + 1;
    }
};

int main()
{
    Solution sol;
    int r;


    r = sol.longestIdealString("lkpkxcigcs", 6);
    cout << r << endl;

    r = sol.longestIdealString("kkkx", 6);
    cout << r << endl;

    r = sol.longestIdealString("ci", 4);
    cout << r << endl;

    r = sol.longestIdealString("aa", 16);
    cout << r << endl;

    r = sol.longestIdealString("slddedwfmo", 16);
    cout << r << endl;

    r = sol.longestIdealString("acfgbd", 2);
    cout << r << endl;
}