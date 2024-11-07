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

class NumArray {
    vector<int> tree;

    void update(int v, int tl, int tr, int l, int r, int addend) {

        if (l > r)
            return;

        if (l == tl && tr == r) {
            tree[v] += addend;
        } else {
            int tm = (tl + tr) / 2;
            update(v * 2, tl, tm, l, min(r, tm), addend);
            update(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, addend);

            /* TODO: use case specific */
            tree[v] = tree[v * 2] + tree[v * 2 + 1];
        }
    }

    int query(int v, int tl, int tr, int l, int r) {

        if (l > r)
            /* TODO: use case specific */
            return 0;

        if (l == tl && tr == r)
            /* leaf nodes */
            return tree[v];

        int tm = (tl + tr) / 2;

        /* TODO: use case specific */
        return query(v * 2, tl, tm, l, min(r, tm)) +
               query(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);
    }

    int _n;

  public:
    NumArray(vector<int>& nums) {
        int n = _n = nums.size();
        tree = vector<int>(4 * n);

        for (auto i = 0; i < n; ++i) {
            update(1, 0, _n - 1, i, i, nums[i]);
        }
    }

    void update(int index, int val) {
        /* call segment tree update */
        auto v = query(1, 0, _n - 1, index, index);
        update(1, 0, _n - 1, index, index, -v);
        update(1, 0, _n - 1, index, index, val);
    }

    int sumRange(int left, int right) {
        return query(1, 0, _n - 1, left, right);
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */

int main() {
    vector<int> init = {1, 3, 5};
    NumArray na(init);
    int r;

    cout << r << endl;
}
