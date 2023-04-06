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
    vector<int> parent;
    vector<vector<int>> children;
    vector<vector<int>> al;
    vector<unordered_set<int>> allChildren;
    vector<int> depth;

    void dfs(int k, int p, int d)
    {
        parent[k] = p;
        depth[k] = d;
        for (auto &n : al[k])
            if (n != p)
                dfs(n, k, d + 1);

        allChildren[k].insert(k);
        for (auto &n : al[k])
            if (n != p)
                allChildren[k].insert(begin(allChildren[n]), end(allChildren[n]));
    }

    int dfs2(int i, int j, int k)
    {
        if (i == j)
            return i;

        if (depth[i] != depth[j])
            if (depth[i] > depth[j])
                swap(i, j);

        if (allChildren[j].count(k))
            return j;

        if (depth[i] == depth[j])
            if (allChildren[i].count(k))
                return i;

        if (depth[i] != depth[j])
            return dfs2(i, parent[j], k);

        return dfs2(parent[i], parent[j], k);
    }

public:
    vector<int> closestNode(int n, vector<vector<int>> &edges, vector<vector<int>> &query)
    {
        parent = vector<int>(n);
        children = vector<vector<int>>(n);
        al = vector<vector<int>>(n);
        allChildren = vector<unordered_set<int>>(n);
        depth = vector<int>(n);

        for (auto &e : edges)
        {
            al[e[0]].push_back(e[1]);
            al[e[1]].push_back(e[0]);
        }

        dfs(0, -1, 0);

        vector<int> rv;
        for (auto &q : query)
            rv.push_back(dfs2(q[0], q[1], q[2]));
        return rv;
    }
};

int main()
{
    Solution sol;
    vector<int> r;

    r = sol.closestNode(7, vector<vector<int>>() = {{0, 1}, {1, 2}}, vector<vector<int>>() = {{0, 2, 1}, {0, 2, 0}, {0, 2, 2}});
    for (auto &c : r)
        cout << c << ", ";
    cout << endl;

    r = sol.closestNode(7, vector<vector<int>>() = {{0, 1}, {1, 2}}, vector<vector<int>>() = {{0, 1, 2}});
    for (auto &c : r)
        cout << c << ", ";
    cout << endl;

    r = sol.closestNode(7, vector<vector<int>>() = {{0, 1}, {0, 2}, {0, 3}, {1, 4}, {2, 5}, {2, 6}}, vector<vector<int>>() = {{5, 3, 4}, {5, 3, 6}});
    for (auto &c : r)
        cout << c << ", ";
    cout << endl;
}