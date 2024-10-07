#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <climits>
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
    int min1(vector<vector<int>>& g, int b, int l, int t,
             int r) { // bottom, left, top, right
        int _b = 30, _l = 30, _t = 0, _r = 0;
        for (int i = b; i < t; ++i)
            for (int j = l; j < r; ++j)
                if (g[i][j]) {
                    _b = min(_b, i);
                    _l = min(_l, j);
                    _t = max(_t, i);
                    _r = max(_r, j);
                }
        return (_t - _b + 1) * (_r - _l + 1);
    }
    int min2v(vector<vector<int>>& g, int b, int l, int t, int r) {
        int res = INT_MAX;
        for (int i = b + 1; i <= t; ++i)
            res = min(res, min1(g, b, l, i, r) + min1(g, i, l, t, r));
        return res;
    }
    int min2h(vector<vector<int>>& g, int b, int l, int t, int r) {
        int res = INT_MAX;
        for (int j = l + 1; j <= r; ++j)
            res = min(res, min1(g, b, l, t, j) + min1(g, b, j, t, r));
        return res;
    }

  public:
    int minimumSum(vector<vector<int>>& g) {
        int res = INT_MAX, m = g.size(), n = g[0].size();
        for (int i = 1; i <= m; ++i)
            res = min({res, min1(g, 0, 0, i, n) + min2h(g, i, 0, m, n),
                       min1(g, i, 0, m, n) + min2h(g, 0, 0, i, n),
                       min1(g, i, 0, m, n) + min2v(g, 0, 0, i, n)});
        for (int j = 1; j <= n; ++j)
            res = min({res, min1(g, 0, 0, m, j) + min2v(g, 0, j, m, n),
                       min1(g, 0, j, m, n) + min2v(g, 0, 0, m, j),
                       min1(g, 0, j, m, n) + min2h(g, 0, 0, m, j)});
        return res;
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.minimumSum(vector<vector<int>>() = {{0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0},
                                                {0, 0, 0, 1, 0},
                                                {1, 1, 0, 0, 0}});
    cout << r << endl;

    r = sol.minimumSum(vector<vector<int>>() = {{1, 0, 1}, {1, 1, 1}});
    cout << r << endl;
}
