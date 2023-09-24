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
    int dfs(int p, int u)
    {
        int rv = 0;
        if (!dp.count({p, u}))
        {
            for (auto &v : al[u])
                if (v != p)
                    rv += dfs(u, v);

            for (auto &v : alr[u])
                if (v != p)
                    rv += dfs(u, v) + 1;
            
            dp[{p, u}] = rv;
        }
        return dp[{p, u}];
    }

    vector<vector<int>> al, alr;
    map<array<int, 2>, int> dp;

public:
    vector<int> minEdgeReversals(int n, vector<vector<int>> &edges)
    {
        // Create al
        al = vector<vector<int>>(n);
        alr = vector<vector<int>>(n);
        for (auto &e : edges)
            al[e[0]].push_back(e[1]),
                alr[e[1]].push_back(e[0]);

        vector<int> rv; 
        for(auto i = 0; i < n; ++i)
            rv.push_back(dfs(i, -1));

        return rv;
    }
};

int main()
{
    Solution sol;
    vector<int> r;

    r = sol.minEdgeReversals(5, vector<vector<int>>() = {{0, 1}, {2, 0}, {0, 4}, {3, 4}});
    for (auto &c : r)
        cout << c << ", ";
    cout << endl;
}