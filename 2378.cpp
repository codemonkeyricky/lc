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
    long long dfs(int k, bool take)
    {
        if (!dp[k][take])
        {
            long long rv = 0, cumulative = 0;
            vector<long long> best(tree[k].size());
            for (int i = 0; i < tree[k].size(); i++)
            {
                auto &[c, w] = tree[k][i];
                best[i] = dfs(c, true);
                cumulative += best[i];
            }
            rv = max(rv, cumulative);
            if (take)
            {
                for (int i = 0; i < tree[k].size(); i++)
                {
                    auto &[c, w] = tree[k][i];
                    auto weight = w + dfs(c, false);
                    weight += cumulative - best[i];
                    rv = max(rv, weight);
                }
            }
            dp[k][take] = rv + 1;
        }
        return dp[k][take] - 1;
    }

    vector<vector<array<long long, 2>>> tree;
    vector<array<long long, 2>> dp;

public:
    long long maxScore(vector<vector<int>> &edges)
    {
        int n = edges.size();
        tree.resize(n);
        dp = vector<array<long long, 2>>(n);
        for (int i = 1; i < n; i++)
            tree[edges[i][0]].push_back({i, edges[i][1]});

        return dfs(0, 1);
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.maxScore(vector<vector<int>>() = {{-1, -1}, {0, 5}, {0, 10}, {2, 6}, {2, 4}});
    cout << r << endl;
}