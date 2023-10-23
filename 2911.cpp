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
#include <cstring>

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

int dp[201][201][201] = {};
class Solution
{
    int semiScore(string &s, int i, int j)
    {
        int rv = 1e9;
        auto ss = s.substr(i, j - i + 1);
        for (auto d = 1; d * 2 <= ss.size(); ++d)
            if (ss.size() % d == 0)
            {
                int r = 0;

                vector<string> str(d);
                for (auto k = 0; k < ss.size(); ++k)
                    str[k % d] += ss[k];

                for (auto &s : str)
                {
                    int ii = 0, jj = s.size() - 1;
                    while (ii < jj)
                        if (s[ii++] != s[jj--])
                            ++r;
                }

                rv = min(rv, r);
            }
        return rv;
    }

    int dfs_topsdown(vector<vector<int>> &semi, int i, int j, int k)
    {
        int n = semi.size();

        if (k == 0)
            return (n - i >= 2) ? semi[i][n - 1] : 1e9;

        if (j >= n - 1)
            return 1e9;

        if (dp[i][j][k] == 0)
        {
            int a = dfs_topsdown(semi, i, j + 1, k);
            int b = semi[i][j] + dfs_topsdown(semi, j + 1, j + 2, k - 1);
            dp[i][j][k] = min(a, b) + 1;
        }
        return dp[i][j][k] - 1;
    }

    int dfs_bottomsup(vector<vector<int>> &semi, int i, int j, int kk)
    {
        int n = semi.size();

        // base case
        for (auto i = 0; i < n; ++i)
            for (auto j = i + 1; j < n; ++j)
                dp[i][j][0] = semi[i][j];

        // bottoms up
        for (auto k = 1; k < kk; ++k)
            for (auto j = 3; j < n; ++j)         ///< 0 ... j
            {
                dp[0][j][k] = 1e9;
                for (auto i = 1; i + 1 < j; ++i) ///< 0... i, i +1 .. j
                    dp[0][j][k] = min(dp[0][j][k], dp[0][i][k - 1] + semi[i + 1][j]);
            }

        return dp[0][n - 1][kk - 1];
    }

    vector<vector<vector<int>>> dp;

public:
    int minimumChanges(string s, int k)
    {
        int n = s.size();
        vector<vector<int>> semi(n, vector<int>(n));

        for (auto i = 0; i < n; ++i)
            for (auto j = i + 1; j < n; ++j)
                semi[i][j] = semiScore(s, i, j);

        dp = vector<vector<vector<int>>>(n, vector<vector<int>>(n, vector<int>(k)));
        // return dfs_topsdown(semi, 0, 1, k - 1);
        return dfs_bottomsup(semi, 0, n - 1, k);
    }
};


int main()
{
    Solution sol;
    int r;

    r = sol.minimumChanges("abcc", 1);
    cout << r << endl;

    r = sol.minimumChanges("acba", 2);
    cout << r << endl;

    r = sol.minimumChanges("abcac", 2);
    cout << r << endl;
}