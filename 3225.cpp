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

#define ll long long
#define B 0
#define W 1
class Solution {
  public:
    ll maximumScore(vector<vector<int>>& grid) {

        int n = grid.size();
        int m = grid[0].size();

        vector<vector<array<ll, 2>>> dp(
            n, vector<array<ll, 2>>(m, array<ll, 2>()));

        for (auto j = 0; j < n; ++j) {
            for (auto i = 0; i < m; ++i) {

                ll prb, prw, pcw, pcb, a, b, c, d;

                /* i, j, B */

                prb = i ? dp[i - 1][j][B] : 0;
                pcw = j ? dp[i][j - 1][W] : 0;
                pcb = j ? dp[i][j - 1][B] : 0;
                // prev row must be also B
                dp[i][j][B] = prb + max({pcw, pcb});

                /* i, j, W */

                ///< prev row can be W or B
                prw = i ? dp[i - 1][j][W] : 0;
                prb = i ? dp[i - 1][j][B] : 0;
                ///< pick W or B from prev col
                pcw = j ? dp[i][j - 1][W] : 0;
                pcb = j ? dp[i][j - 1][B] : 0;

                /* prev row can be B or W */
                /* prev col: if B then can use grid[i][j] */
                dp[i][j][W] = max({prw, prb}) + max({pcb + grid[i][j], pcw});
            }
        }

        ll rv = 0;
        for (auto i = 0; i < m; ++i)
            for (auto j = 0; j < n; ++j)
                for (auto k = 0; k < 2; ++k)
                    rv = max(rv, dp[i][j][k]);

        return rv;
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.maximumScore(vector<vector<int>>() = {{0, 0, 0, 0, 0},
                                                  {0, 0, 3, 0, 0},
                                                  {0, 1, 0, 0, 0},
                                                  {5, 0, 0, 3, 0},
                                                  {0, 0, 0, 0, 2}});
    cout << r << endl;
}
