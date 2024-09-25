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

class Solution {

    int query(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return -1e9;
        if (l == tl && tr == r)
            return tree[v];
        int tm = (tl + tr) / 2;
        return max(query(v * 2, tl, tm, l, min(r, tm)),
                   query(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r));
    }

    void update(int v, int tl, int tr, int l, int r, int addend) {
        if (l > r)
            return;
        if (l == tl && tr == r) {
            tree[v] = addend;
        } else {
            int tm = (tl + tr) / 2;
            update(v * 2, tl, tm, l, min(r, tm), addend);
            update(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, addend);
            tree[v] = max(tree[v * 2], tree[v * 2 + 1]);
        }
    }

    vector<int> tree;
    set<int> set;

  public:
    vector<bool> getResults(vector<vector<int>>& queries) {
        int n = 5 * 1e4;
        tree = vector<int>(n * 4);

        set.insert(0), set.insert(n);
        update(1, 1, n, n, n, n);

        vector<bool> rv;
        for (auto& q : queries) {
            if (q[0] == 1) {
                auto m = q[1];

                auto it = set.insert(m).first;
                auto pp = *prev(it);
                auto nn = *next(it);

                update(1, 1, n, nn, nn, nn - m);
                update(1, 1, n, m, m, m - pp);
            } else if (q[0] == 2) {
                auto p = q[1];
                auto sz = q[2];

                auto m = *prev(set.upper_bound(p));
                if (m == 0) {
                    rv.push_back(p >= sz);
                } else {
                    auto gap = query(1, 1, n, 1, m);
                    if (gap >= sz || p - m >= sz)
                        rv.push_back(true);
                    else
                        rv.push_back(false);
                }
            }
        }

        return rv;
    }
};

int main() {
    Solution sol;
    vector<bool> r;

    r = sol.getResults(
        vector<vector<int>>() = {{1, 5}, {1, 7}, {2, 4, 11}, {2, 7, 3}});

    r = sol.getResults(vector<vector<int>>() = {{1, 1}, {2, 4, 3}});

    r = sol.getResults(vector<vector<int>>() = {{2, 1, 1}});

    r = sol.getResults(vector<vector<int>>() = {
                           {1, 7}, {2, 7, 6}, {1, 2}, {2, 7, 5}, {2, 7, 6}});

    r = sol.getResults(
        vector<vector<int>>() = {{1, 2}, {2, 3, 3}, {2, 3, 1}, {2, 2, 2}});
    // for (auto rr : r)
    //     cout << r << ", " << endl;
}
