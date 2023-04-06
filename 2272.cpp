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
    int largestVariance(string s)
    {
        int n = s.size();
        vector<array<int, 26>> dp(n);
        vector<vector<int>> q(26);
        for (auto i = 0; i < n; ++i)
        {
            int k = s[i] - 'a';
            if (i)
                dp[i] = dp[i - 1];
            ++dp[i][k];
            q[k].push_back(i);
        }

        array<int, 26> empty = {};
        int rv = 0;
        for (auto i = 0; i < 26; ++i)
        {
            int r2 = 0;
            for (auto j = 0; j < q[i].size(); ++j)
            {
                array<int, 26> *l, *r;
                l = (j) ? l = &dp[q[i][j - 1]] : &empty;
                r = (j < q[i].size() - 1) ? &dp[q[i][j + 1] - 1] : &dp[n - 1];
                for (auto k = 0; k < 26; ++k)
                    if (k != i)
                        r2 = max(r2, abs((*l)[k] - (*r)[k]));
                r2 = (r2 == 0) ? 0 : abs(r2 - 1);
                rv = max(r2, rv);
            }
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.largestVariance("aabbbbaa");
    cout << r << endl;

    r = sol.largestVariance("aababbb");
    cout << r << endl;
}