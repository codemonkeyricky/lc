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
    void add(int n, int l, int r, int i, int j) {
        if (lazy[n]) {
            // node is within invert range
            tree[n] = (r - l + 1) - tree[n];

            // every node below need to be inverted because already in range.
            if (l != r) {
                lazy[n * 2] = !lazy[n * 2];
                lazy[n * 2 + 1] = !lazy[n * 2 + 1];
            }

            lazy[n] = 0;
        }

        // case 1: skip if region not of interest
        if (j < l || i > r)
            return;

        // case 2: in range
        if (i <= l && r <= j) {
            // node is within invert range
            tree[n] = (r - l + 1) - tree[n];

            // every node below need to be inverted because already in range.
            if (l != r) {
                lazy[n * 2] = !lazy[n * 2];
                lazy[n * 2 + 1] = !lazy[n * 2 + 1];
            }

            return;
        }

        // case 3:
        int m = (l + r) / 2;

        add(n * 2, l, m, i, j);
        add(n * 2 + 1, m + 1, r, i, j);

        tree[n] = tree[n * 2] + tree[n * 2 + 1];
    }

    int query(int n, int l, int r, int i, int j) {
        if (lazy[n]) {
            // node is within invert range
            tree[n] = (r - l + 1) - tree[n];

            // every node below need to be inverted because already in range.
            if (l != r) {
                lazy[n * 2] = !lazy[n * 2];
                lazy[n * 2 + 1] = !lazy[n * 2 + 1];
            }

            lazy[n] = 0;
        }

        if (j < l || i > r)
            return 0;

        // node in range
        if (i <= l && r <= j)
            return tree[n];

        // case 3
        int m = (l + r) / 2;
        int p1 = query(n * 2, l, m, i, j);
        int p2 = query(n * 2 + 1, m + 1, r, i, j);
        return p1 + p2;
    }

    vector<int> tree, lazy;

  public:
    vector<bool> getResults(vector<vector<int>>& queries) {
        int n = 5 * 1e4 + 1;
        tree = vector<int>(n * 4);
        lazy = vector<int>(n * 4);
    }
};

int main() {
    Solution sol;
    int r;

    cout << r << endl;
}
