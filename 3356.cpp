#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x), left(left), right(right) {}
};

TreeNode* recurse(vector<int>& tree, int k) {
    if (k >= tree.size() || tree[k] == -1)
        return nullptr;

    return new TreeNode(tree[k], recurse(tree, k * 2 + 1),
                        recurse(tree, k * 2 + 2));
}

TreeNode* populate(vector<int>& tree) { return recurse(tree, 0); }

void pvi(vector<int>& v) {

    for (auto& vv : v)
        cout << vv << ", ";
    cout << endl;
}

using vi = vector<int>;
using vvi = vector<vector<int>>;
using vll = vector<long long>;
using vvll = vector<vector<long long>>;

class Solution {
    vector<int> tree, lazy;

    /* for range update */
    void push(int v) {
        tree[v * 2] += lazy[v];
        lazy[v * 2] += lazy[v];
        tree[v * 2 + 1] += lazy[v];
        lazy[v * 2 + 1] += lazy[v];
        lazy[v] = 0;
    }

    void update(int v, int tl, int tr, int l, int r, int addend) {

        if (l > r)
            return;

        if (l == tl && tr == r) {
            tree[v] += addend;
            lazy[v] += addend; /* range update */
        } else {
            push(v); /* range update */
            int tm = (tl + tr) / 2;
            update(v * 2, tl, tm, l, min(r, tm), addend);
            update(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, addend);

            tree[v] = max(tree[v * 2], tree[v * 2 + 1]);
        }
    }

    int query(int v, int tl, int tr, int l, int r) {

        if (l > r)
            /* TODO: use case specific */
            return 0;

        if (l == tl && tr == r)
            /* leaf nodes */
            return tree[v];

        push(v); /* range update */
        int tm = (tl + tr) / 2;

        return max(query(v * 2, tl, tm, l, min(r, tm)),
                   query(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r));
    }

    int n;

  public:
    int minZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();

        tree = lazy = vector<int>(4 * n);

        for (auto i = 0; i < n; ++i) {
            update(1, 0, n - 1, i, i, nums[i]);
        }

        int k = 0;
        for (auto& q : queries) {
            auto l = q[0], r = q[1], v = q[2];

            if (query(1, 0, n - 1, 0, n - 1) <= 0) {
                return k;
            }

            update(1, 0, n - 1, l, r, -v);
            ++k;
        }

        if (query(1, 0, n - 1, 0, n - 1) <= 0) {
            return k;
        }

        return -1;
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.minZeroArray(vector<int>() = {2},
                         vector<vector<int>>() = {{0, 0, 3}, {0, 0, 3}});
    cout << r << endl;

    r = sol.minZeroArray(
        vector<int>() = {2, 0, 2},
        vector<vector<int>>() = {{0, 2, 1}, {0, 2, 1}, {1, 1, 3}});
    cout << r << endl;
}
