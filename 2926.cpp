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
    vector<long long> lazy, tree;

    void push(int v)
    {
        tree[v * 2] += lazy[v];
        lazy[v * 2] += lazy[v];
        tree[v * 2 + 1] += lazy[v];
        lazy[v * 2 + 1] += lazy[v];
        lazy[v] = 0;
    }

    void update(int v, int tl, int tr, int l, int r, long long addend)
    {
        if (l > r)
            return;
        if (l == tl && tr == r)
        {
            tree[v] += addend;
            lazy[v] += addend;
        }
        else
        {
            push(v);
            int tm = (tl + tr) / 2;
            update(v * 2, tl, tm, l, min(r, tm), addend);
            update(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, addend);
            tree[v] = max(tree[v * 2], tree[v * 2 + 1]);
        }
    }

    long long query(int v, int tl, int tr, int l, int r)
    {
        if (l > r)
            return -1e9 - 2;
        if (l == tl && tr == r)
            return tree[v];
        push(v);
        int tm = (tl + tr) / 2;
        return max(query(v * 2, tl, tm, l, min(r, tm)),
                   query(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r));
    }

public:
    long long maxBalancedSubsequenceSum(vector<int> &nums)
    {
        int n = nums.size();
        set<int> uniq;
        for (auto i = 0; i < n; ++i)
            uniq.insert(nums[i] - i);

        unordered_map<int, int> lookup;
        int k = 0;
        for (auto &u : uniq)
            lookup[u] = k++;

        vector<int> nums2;
        for (auto i = 0; i < n; ++i)
            nums2.push_back(lookup[nums[i] - i]);

        lazy = tree = vector<long long>(n * 4);

        for (auto i = 0; i < n; ++i)
            update(1, 0, n - 1, i, i, -1e9 - 1);

        for (auto i = 0; i < n; ++i)
        {
            auto k = nums2[i];
            auto v = query(1, 0, n - 1, 0, k);
            auto reset = query(1, 0, n - 1, k, k);
            update(1, 0, n - 1, k, k, -reset);
            update(1, 0, n - 1, k, k, (v < 0 ? 0 : v) + nums[i]);
        }

        return query(1, 0, n - 1, 0, n - 1);
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.maxBalancedSubsequenceSum(vector<int>() = {-2, -1});
    cout << r << endl;

    r = sol.maxBalancedSubsequenceSum(vector<int>() = {5, -1, -3, 8});
    cout << r << endl;

    r = sol.maxBalancedSubsequenceSum(vector<int>() = {3, 3, 5, 6});
    cout << r << endl;
}