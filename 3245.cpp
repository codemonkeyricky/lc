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

    // initialize to 4*n
    vector<int> tree;

    void update(vector<int>& tree, int v, int tl, int tr, int l, int r,
                int addend) {
        if (l > r)
            return;
        if (l == tl && tr == r) {
            tree[v] += addend;
        } else {
            // push(v);
            int tm = (tl + tr) / 2;
            update(tree, v * 2, tl, tm, l, min(r, tm), addend);
            update(tree, v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, addend);
            tree[v] = tree[v * 2] + tree[v * 2 + 1];
        }
    }

    int query(vector<int>& tree, int v, int tl, int tr, int l, int r) {
        if (l > r)
            return 0;
        if (l == tl && tr == r)
            return tree[v];
        int tm = (tl + tr) / 2;
        return query(tree, v * 2, tl, tm, l, min(r, tm)) +
               query(tree, v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);
    }

  public:
    vector<int> numberOfAlternatingGroups(vector<int>& colors,
                                          vector<vector<int>>& queries) {
        vector<int> sum, cnt;
        int n = colors.size();
        sum = cnt = vector<int>(4 * n);

        set<array<int, 2>> streaks;

        int streak = 1;
        for (auto i = 1; i < n * 2; ++i) {
            if (colors[(i - 1) % n] != colors[i % n]) {
                ++streak;
            } else {
                update(cnt, 1, 1, n, streak, streak, 1);
                update(sum, 1, 1, n, streak, streak, streak);
                streaks.insert({i - streak, streak});
                streak = 1;

                if (i >= n)
                    break;
            }
        }

        vector<int> rv;
        for (auto& q : queries) {
            if (q[0] == 1) {
                int s = query(sum, 1, 1, n, q[1], n);
                int c = query(cnt, 1, 1, n, q[1], n);

                rv.push_back(s - q[1] * c + c);
            } else {
            }
        }

        return rv;
    }
};

int main() {
    Solution sol;
    vector<int> r;

    r = sol.numberOfAlternatingGroups(
        vector<int>() = {0, 0, 1, 0, 1},
        vector<vector<int>>() = {{2, 1, 0}, {1, 4}});
    for (auto& rr : r) {
        cout << rr << ", " << endl;
    }
}

// update(sum, 1, 1, n, 4, 4, 4);
// update(sum, 1, 1, n, 4, 4, 4);
// update(sum, 1, 1, n, 3, 3, 7);
// update(sum, 1, 1, n, 3, 3, -7);
// update(sum, 1, 1, n, 1, 1, -2);
// cout << query(sum, 1, 1, n, 1, n) << endl;
