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
    int timer, l;
    vector<int> tin, tout;
    vector<vector<int>> up;
    vector<vector<array<int, 2>>> al; //< index, weight
    vector<array<int, 27>> weight;

    void bl(int v, int p)
    {
        tin[v] = ++timer;
        up[v][0] = p;
        for (int i = 1; i <= l; ++i)
            up[v][i] = up[up[v][i - 1]][i - 1];
        for (auto [u, w] : al[v])
            if (u != p)
                bl(u, v);

        tout[v] = ++timer;
    }

    void dfs(int v, int p, array<int, 27> &w)
    {
        weight[v] = w;
        for (auto [u, ww] : al[v])
            if (u != p)
            {
                ++w[ww];
                dfs(u, v, w);
                --w[ww];
            }
    }

    bool isAncester(int u, int v)
    {
        return tin[u] <= tin[v] && tout[u] >= tout[v];
    }

    int lca(int u, int v)
    {
        if (isAncester(u, v))
            return u;
        if (isAncester(v, u))
            return v;
        for (int i = l; i >= 0; --i)
            if (!isAncester(up[u][i], v))
                u = up[u][i];
        return up[u][0];
    }

public:
    vector<int> minOperationsQueries(int n, vector<vector<int>> &edges, vector<vector<int>> &queries)
    {
        al.resize(n);
        for (auto &e : edges)
            al[e[0]].push_back({e[1], e[2]}),
                al[e[1]].push_back({e[0], e[2]});

        tin.resize(n);
        tout.resize(n);
        timer = 0;
        l = ceil(log2(n));
        up.assign(n, vector<int>(l + 1));
        bl(0, 0);

        weight.resize(n);
        array<int, 27> w = {};
        dfs(0, 0, w);

        vector<int> rv;
        for (auto &q : queries)
        {
            int b = q[0], c = q[1];
            auto a = lca(b, c);
            auto aa = weight[a];
            auto bb = weight[b];
            auto cc = weight[c];
            w = {};
            int edges = 0, mmax = 0;
            for (auto i = 0; i < 27; ++i)
            {
                w[i] = bb[i] + cc[i] - 2 * aa[i];
                mmax = max(mmax, w[i]);
                edges += w[i];
            }
            rv.push_back(edges - mmax);
        }
        return rv;
    }
};


int main()
{
    Solution sol;
    int r;


    sol.minOperationsQueries(8, vector<vector<int>>() = {{1, 2, 6}, {1, 3, 4}, {2, 4, 6}, {2, 5, 3}, {3, 6, 6}, {3, 0, 8}, {7, 0, 2}}, vector<vector<int>>() = {{4, 6}, {0, 4}, {6, 5}, {7, 4}});
}