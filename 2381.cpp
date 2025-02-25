#include <algorithm>
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
    vector<int> tree, lazy;

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
            lazy[v] += addend;
        } else {
            push(v); /* range update */
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

        push(v); /* range update */
        int tm = (tl + tr) / 2;

        /* TODO: use case specific */
        return query(v * 2, tl, tm, l, min(r, tm)) +
               query(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);
    }

    int n;

  public:
    string shiftingLetters(string s, vector<vector<int>>& shifts) {

        n = s.size();
        tree = lazy = vector<int>(4 * n);

        for (auto& shift : shifts) {
            auto l = shift[0];
            auto r = shift[1];
            auto add = shift[2] ? 1 : -1;
            update(1, 0, n - 1, l, r, add);
        }

        auto rv = s;
        for (auto i = 0; i < n; ++i) {
            auto shift = query(1, 0, n - 1, i, i);
            rv[i] = (((rv[i] - 'a') + shift) % 26 + 26) % 26 + 'a';
        }
        return rv;
    }
};

int main() {
    Solution sol;
    string r;

    r = sol.shiftingLetters("xuwdbdqik", vector<vector<int>>() = {{4, 8, 0},
                                                                  {4, 4, 0},
                                                                  {2, 4, 0},
                                                                  {2, 4, 0},
                                                                  {6, 7, 1},
                                                                  {2, 2, 1},
                                                                  {0, 2, 1},
                                                                  {8, 8, 0},
                                                                  {1, 3, 1}});
    cout << r << endl;

    r = sol.shiftingLetters("dztz",
                            vector<vector<int>>() = {{0, 0, 0}, {1, 1, 1}});
    cout << r << endl;

    r = sol.shiftingLetters(
        "abc", vector<vector<int>>() = {{0, 1, 0}, {1, 2, 1}, {0, 2, 1}});
    cout << r << endl;
}