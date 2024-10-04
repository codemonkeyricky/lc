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
  public:
    int minFlips(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        int rv = 0;
        for (auto i = 0; i < m; ++i)
            for (auto j = 0; j < n; ++j)
                rv += grid[i][j];

        if (m == n && n % 2 == 1) {
            int r = 0;
            for (auto i = 0; i < m / 2 + 1; ++i) {
                for (auto j = 0; j < n / 2 + 1; ++j) {
                }
            }

            rv = min(rv, r);
        }

        return rv;
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.minFlips(vector<vector<int>>() = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}});
    cout << r << endl;
}
