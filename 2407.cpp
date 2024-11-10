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
  public:
    int st[2 * (1 << 17)] = {}; // 2 ^ 16 < 100000 < 2 ^ 17
    int query(int l, int r, int p = 1, int tl = 0, int tr = 100000) {
        if (l > r)
            return 0;
        if (l == tl && r == tr)
            return st[p];
        int tm = (tl + tr) / 2;
        return max(query(l, min(r, tm), p * 2, tl, tm),
                   query(max(l, tm + 1), r, p * 2 + 1, tm + 1, tr));
    }
    int update(int pos, int new_val, int p = 1, int tl = 0, int tr = 100000) {
        if (tl == tr)
            return st[p] = new_val;
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            return st[p] =
                       max(update(pos, new_val, p * 2, tl, tm), st[p * 2 + 1]);
        return st[p] =
                   max(st[p * 2], update(pos, new_val, p * 2 + 1, tm + 1, tr));
    }

    int lengthOfLIS(vector<int>& nums, int k) {
        return accumulate(begin(nums), end(nums), 0, [&](int res, int n) {
            /* use segment tree to find max between n-k to n-1 */
            return update(n, query(max(0, n - k), n - 1) + 1);
        });
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.lengthOfLIS(vector<int>() = {4, 2, 1, 4, 3, 4, 5, 8, 15}, 3);
    cout << r << endl;
}