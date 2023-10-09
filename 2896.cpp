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
    int dfs(string &s1, string &s2, int f, int x, int k)
    {
        int n = s1.size();
        if (k >= n)
            return f ? 1e9 : 0;

        if (dp[k][f] == 0)
        {
            int rv = 0;
            if (s1[k] == s2[k] && f == 0)
                rv = dfs(s1, s2, 0, x, k + 1);
            else if (s1[k] != s2[k] && f != 0)
                rv = dfs(s1, s2, 0, x, k + 1);
            else
            {
                // flip again
                int a = 1 + dfs(s1, s2, 1, x, k + 1);

                // find the next mismatch
                int b = 1e9;
                for (auto i = k + 1; i < n && b == 1e9; ++i)
                    if (s1[i] != s2[i])
                        b = x + dfs(s1, s2, 0, x, i + 1);

                rv = min(a, b);
            }
            dp[k][f] = rv + 1;
        }
        return dp[k][f] - 1;
    }

    vector<vector<int>> dp;

public:
    int minOperations(string s1, string s2, int x)
    {
        dp = vector<vector<int>>(s1.size(), vector<int>(2));
        int rv = dfs(s1, s2, 0, x, 0);
        return rv >= 1e9 ? -1 : rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minOperations("10110", "00011", 4);
    cout << r << endl;

    r = sol.minOperations("1100011000", "0101001010", 2);
    cout << r << endl;
}