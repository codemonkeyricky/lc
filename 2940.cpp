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
    void update(int v, int tl, int tr, int l, int r, int value)
    {
        if (l > r)
            return;
        if (l == tl && tr == r)
            tree[v] = value;
        else
        {
            int tm = (tl + tr) / 2;
            update(v * 2, tl, tm, l, min(r, tm), value);
            update(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, value);
            tree[v] = max(tree[v * 2], tree[v * 2 + 1]);
        }
    }

    int query(int v, int tl, int tr, int l, int r)
    {
        if (l > r)
            return -1e9;
        if (l == tl && tr == r)
            return tree[v];
        int tm = (tl + tr) / 2;
        return max(query(v * 2, tl, tm, l, min(r, tm)),
                   query(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r));
    }

    vector<int> tree;

public:
    vector<int> leftmostBuildingQueries(vector<int> &heights, vector<vector<int>> &queries)
    {
        int n = heights.size();
        tree = vector<int>((n + 1) * 4);

        for (auto i = 0; i < n; ++i)
            update(1, 0, n, i, i, heights[i]);

        vector<int> rv;
        for (auto &q : queries)
        {
            // make sure a is always to the left of b
            int a = q[0], b = q[1];
            if (a > b)
                swap(a, b);

            if (a == b || heights[a] < heights[b])
            {
                rv.push_back(b);
                continue;
            }

            int l = max(a, b), r = n - 1;
            while (l < r)
            {
                int m = (l + r) / 2;
                int h = query(1, 0, n, l, m);
                if (heights[a] < h && heights[b] < h)
                    r = m;
                else
                    l = m + 1;
            }

            if (heights[a] < heights[l] && heights[b] < heights[l])
                rv.push_back(l);
            else
                rv.push_back(-1);
        }

        return rv;
    }
};

int main()
{
    Solution sol;
    vector<int> r;

    r = sol.leftmostBuildingQueries(
        vector<int>() = {5, 3, 8, 2, 6, 1, 4, 6},
        vector<vector<int>>() = {{0, 7}, {3, 5}, {5, 2}, {3, 0}, {1, 6}});
    for (auto &rr : r)
        cout << rr << ", ";
    cout << endl;

    r = sol.leftmostBuildingQueries(vector<int>() = {6, 4, 8, 5, 2, 7}, vector<vector<int>>() = {{0, 1}, {0, 3}, {2, 4}, {3, 4}, {2, 2}});
    for (auto &rr : r)
        cout << rr << ", ";
    cout << endl;
}