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
    long dfs(vector<set<int>> &al, int k, int d, long mask)
    {
        if (k == d)
            return mask;
        long rv = 0;
        for (auto &n : al[k])
            if (!(mask & (1ll << n)))
                if (rv = dfs(al, n, d, mask | (1ll << n)))
                    return rv;
        return 0;
    }

    int dfs2(vector<set<int>> &al, vector<int> &count, vector<int> &price, int p, int k, int half)
    {
        int curr = count[k] * price[k];

        if (!dp[k][half])
        {
            int rv = curr / (1 + half);
            for (auto &n : al[k])
                if (n != p)
                {
                    int h = dfs2(al, count, price, k, n, 1);
                    int f = dfs2(al, count, price, k, n, 0);
                    if (half)
                        rv += f;
                    else
                        rv += min(f, h);
                }

            dp[k][half] = rv + 1;
        }

        return dp[k][half] - 1;
    }

    vector<array<int, 2>> dp;

public:
    int minimumTotalPrice(int n, vector<vector<int>> &edges, vector<int> &price, vector<vector<int>> &trips)
    {
        vector<set<int>> al(n);
        for (auto &e : edges)
            al[e[0]].insert(e[1]), al[e[1]].insert(e[0]);

        vector<int> count(n);
        for (auto &trip : trips)
        {
            auto visited = dfs(al, trip[0], trip[1], 1ll << trip[0]);
            for (auto i = 0; i < n; ++i)
                if (visited & (1ll << i))
                    ++count[i];
        }

        dp = vector<array<int, 2>>(n);
        return min(dfs2(al, count, price, -1, 0, 0), dfs2(al, count, price, -1, 0, 1));
    }
};


int main()
{
    Solution sol;
    int r;

    r = sol.minimumTotalPrice(4, vector<vector<int>>() = {{0, 1}, {1, 2}, {1, 3}}, vector<int>() = {2, 2, 10, 6}, vector<vector<int>>() = {{0, 3}, {2, 1}, {2, 3}});
    cout << r << endl;
}