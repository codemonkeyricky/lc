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
    void push(int v)
    {
        tree[v * 2] += lazy[v];
        lazy[v * 2] += lazy[v];
        tree[v * 2 + 1] += lazy[v];
        lazy[v * 2 + 1] += lazy[v];
        lazy[v] = 0;
    }

    void update(int v, int tl, int tr, int l, int r, int diff)
    {
        if (l > r)
            return;
        if (l == tl && tr == r)
        {
            tree[v] += diff;
            lazy[v] += diff;
        }
        else
        {
            push(v);
            int tm = (tl + tr) / 2;
            update(v * 2, tl, tm, l, min(r, tm), diff);
            update(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, diff);
            tree[v] = max(tree[v * 2], tree[v * 2 + 1]);
        }
    }

    int query(int v, int tl, int tr, int l, int r)
    {
        if (l > r)
            return -1e9;
        if (l == tl && tr == r)
            return tree[v];
        push(v);
        int tm = (tl + tr) / 2;
        return max(query(v * 2, tl, tm, l, min(r, tm)),
                   query(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r));
    }

    vector<int> tree, lazy;
public:
    int maxProfit(vector<int> &prices, vector<int> &profits)
    {
        int n = prices.size();

        tree = lazy = vector<int>(5001 * 4);
        update(1, 0, 5000, 0, 5000, -1);

        vector<int> r(n, -1);
        for (int i = n - 1; i >= 0; --i)
        {
            int mmax = query(1, 0, 5000, prices[i] + 1, 5000);
            if (mmax != -1)
                r[i] = mmax;
            int reset = query(1, 0, 5000, prices[i], prices[i]);
            if (reset <= profits[i])
                update(1, 0, 5000, prices[i], prices[i], -reset + profits[i]);
        }

        tree = lazy = vector<int>(5001 * 4);
        update(1, 0, 5000, 0, 5000, -1);

        int rv = -1;
        for (int i = 0; i < n; ++i)
        {
            int mmax = query(1, 0, 5000, 0, prices[i] - 1);
            if (mmax != -1 && r[i] != -1)
                rv = max(rv, mmax + profits[i] + r[i]);

            int reset = query( 1, 0, 5000, prices[i], prices[i]);
            if (reset <= profits[i])
                update(1, 0, 5000, prices[i], prices[i], -reset + profits[i]);
        }

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.maxProfit(vector<int>() = {1, 2, 11, 11}, vector<int>() = {45, 7, 96, 20});
    cout << r << endl;

    r = sol.maxProfit(vector<int>() = {10, 2, 3, 4}, vector<int>() = {100, 2, 7, 10});
    cout << r << endl;
}