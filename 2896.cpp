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
    int dfs(vector<int> &diff, int x, int k, int p) 
    {
        int n = diff.size();
        if (k >= n)
            return p * x;

        if (p == 0)
            return 0;

        if (dp[k][p] == 0)
        {
            int a = 1e9, b = 1e9;
            if (k + 1 < n)
                a = (diff[k + 1] - diff[k]) + dfs(diff, x, k + 2, p - 1);
            b = dfs(diff, x, k + 1, p);
            dp[k][p] = min(a, b) + 1;
        }

        return dp[k][p] - 1;
    }

    vector<vector<int>> dp;

public:
    int minOperations(string s1, string s2, int x)
    {
        int n = s1.size();

        vector<int> diff;
        for (auto i = 0; i < n; ++i)
            if (s1[i] != s2[i])
                diff.push_back(i);

        if (diff.size() % 2)
            return -1;

        dp = vector<vector<int>>(n, vector<int>(diff.size() + 1));
        return dfs(diff, x, 0, diff.size() / 2);
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minOperations("11001011111", "01111000110", 2);
    cout << r << endl;

    r = sol.minOperations("10110", "00011", 4);
    cout << r << endl;

    r = sol.minOperations("1100011000", "0101001010", 2);
    cout << r << endl;
}