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

class BookMyShow
{
public:
    vector<pair<long long, int>> st;
    int g[50001] = {}, n = 0, m = 0, start = 0;
    long long query(int tl, int tr, int l, int r, int p = 1)
    {
        if (l > r)
            return 0;
        if (l == tl && r == tr)
            return st[p].first;
        int tm = (tl + tr) / 2;
        return query(tl, tm, l, min(r, tm), p * 2) + query(tm + 1, tr, max(l, tm + 1), r, p * 2 + 1);
    }

    int get_first_ge(int lv, int rv, int x, int p = 1)
    {
        if (st[p].second < x)
            return -1;
        while (lv != rv)
        {
            int mid = lv + (rv - lv) / 2;
            if (st[2 * p].second >= x)
            {
                p *= 2;
                rv = mid;
            }
            else
            {
                p = 2 * p + 1;
                lv = mid + 1;
            }
        }
        return lv;
    }

    void update(int l, int r, int m, int new_val, int p = 1)
    {
        if (l == r)
            st[p] = {new_val, m - new_val};
        else
        {
            int tm = (l + r) / 2;
            if (m <= tm)
                update(l, tm, m, new_val, p * 2);
            else
                update(tm + 1, r, m, new_val, p * 2 + 1);
            st[p] = {st[p * 2].first + st[p * 2 + 1].first, max(st[p * 2].second, st[p * 2 + 1].second)};
        }
    }
    BookMyShow(int n, int m) : n(n), m(m)
    {
        st = vector<pair<long long, int>>(n * 4, {0, m});
    }
    vector<int> gather(int k, int maxRow)
    {
        int i = get_first_ge(0, n - 1, k);
        if (i < 0 || i > maxRow)
            return {};
        g[i] += k;
        update(0, n - 1, i, g[i]);
        return {i, g[i] - k};
    }
    bool scatter(int k, int maxRow)
    {
        if (query(0, n - 1, 0, maxRow) + k > ((long long)maxRow + 1) * m)
            return false;
        for (int i = start; k && i <= maxRow; ++i)
        {
            if (m - g[i])
            {
                int take = min(m - g[i], k);
                k -= take;
                g[i] += take;
                update(0, n - 1, i, g[i]);
            }
            else
                start = i + 1;
        }
        return true;
    }
};

/**
 * Your BookMyShow object will be instantiated and called as such:
 * BookMyShow* obj = new BookMyShow(n, m);
 * vector<int> param_1 = obj->gather(k,maxRow);
 * bool param_2 = obj->scatter(k,maxRow);
 */

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}