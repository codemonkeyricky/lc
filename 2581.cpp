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
    vector<map<int, int>> dp;

    int dfs(vector<set<int>> &al, vector<set<int>> &guesses, int p, int k)
    {
        if (dp[k].count(p))
            return dp[k][p];

        int correct = 0;
        if (p != -1)
            correct += guesses[p].count(k);

        for (auto &n : al[k])
            if (n != p)
                correct += dfs(al, guesses, k, n);

        return dp[k][p] = correct;
    }

public:
    int rootCount(vector<vector<int>> &edges, vector<vector<int>> &guesses, int k)
    {
        int n = 0;
        for (auto &e : edges)
        {
            if (e[0] > e[1])
                swap(e[0], e[1]);
            n = max(n, e[1] + 1);
        }

        dp = vector<map<int, int>>(n);
        vector<set<int>> al(n);
        for (auto &e : edges)
            al[e[0]].insert(e[1]), al[e[1]].insert(e[0]);

        vector<set<int>> gset(n);
        for (auto &g : guesses)
            gset[g[0]].insert(g[1]);

        int rv = 0;
        for (auto i = 0; i < n; ++i)
            if (dfs(al, gset, -1, i) >= k)
                ++rv;

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.rootCount(vector<vector<int>>() = {{0, 1}, {1, 2}, {1, 3}, {4, 2}}, vector<vector<int>>() = {{1, 3}, {0, 1}, {1, 0}, {2, 4}}, 3);
    cout << r << endl;
}