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

using vi = vector<int>;
using vvi = vector<vector<int>>;
using vll = vector<long long>;
using vvll = vector<vector<long long>>;

class Solution {

    bool is_valid(vvi& b, int i, int j) {
        int n = b.size();

        // vertical
        for (auto ii = i; ii >= 0; --ii)
            if (b[ii][j])
                return false;

        // lr diag
        for (auto ii = i, jj = j; ii >= 0 && jj >= 0; --ii, --jj) {
            if (b[ii][jj])
                return false;
        }

        // rl diag
        for (auto ii = i, jj = j; ii >= 0 && jj < n; --ii, ++jj) {
            if (b[ii][jj])
                return false;
        }

        return true;
    }

    int dfs(vvi& b, int i) {

        int n = b.size();

        if (i >= n)
            return 1;

        int rv = 0;
        for (auto j = 0; j < n; ++j) {
            if (is_valid(b, i, j)) {
                b[i][j] = true;
                rv += dfs(b, i + 1);
                b[i][j] = false;
            }
        }
        return rv;
    }

  public:
    int totalNQueens(int n) {
        vvi b(n, vi(n));
        return dfs(b, 0);
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.totalNQueens(4);
    cout << r << endl;
}
