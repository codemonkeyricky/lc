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
    vector<bool> canMakePaliQueries(string s, vector<vector<int>> &queries)
    {
        int n = s.size();
        vector<array<int, 26>> dp(n);
        for (auto i = 0; i < s.size(); ++i)
        {
            if (i)
                dp[i] = dp[i - 1];
            ++dp[i][s[i] - 'a'];
        }

        vector<bool> rv;
        for (auto &q : queries)
        {
            auto l = q[0], r = q[1], k = q[2];
            auto odd = 0;
            for (auto i = 0; i < 26; ++i)
                odd += (dp[r][i] - (l ? dp[l - 1][i] : 0)) % 2;
            rv.push_back(k >= odd / 2);
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    sol.canMakePaliQueries("abcda", vector<vector<int>>() = {{3, 3, 0}, {1, 2, 0}, {0, 3, 1}, {0, 3, 2}, {0, 4, 1}});
}