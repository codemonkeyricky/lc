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

        vector<vector<ll>> dpw(m, vector<ll>(n));
        vector<vector<ll>> dpb(m, vector<ll>(n));

        for (auto i = 0; i < m; ++i) {
            for (auto j = 0; j < n; ++j) {

                ll prb, prw, pcw, pcb, prcw, prcb;

                /* i, j, B */

                // prb = i ? dpb[i - 1][j] : 0;
                // pcw = j ? dpw[i][j - 1] : 0;
                // pcb = j ? dpb[i][j - 1] : 0;
                // prev row must be also B
                // dpb[i][j] = prb + max({pcw, pcb});

                /* i, j, W */

                prw = i ? dpw[i - 1][j] : 0;
                prb = i ? dpb[i - 1][j] : 0;
                pcw = j ? dpw[i][j - 1] : 0;
                pcb = j ? dpb[i][j - 1] : 0;
                prcw = j && i ? dpw[i - 1][j - 1] : 0;
                prcb = j && i ? dpb[i - 1][j - 1] : 0;

                /* b b */
                dpb[i][j] = max(dpb[i][j], prb + pcb - prcb);
                /* w is not possible when prev row is */

                /* w w */
                dpb[i][j] = max(dpb[i][j], prw + pcw - prcw);
                /* w is not possible when prev col is w */

                /* w b */
                dpb[i][j] = max(dpb[i][j], pcw + pcw - prcw);

                /* b w */

                /* prev row can be B or W */
                /* prev col: if B then can use grid[i][j] */
                // dpw[i][j] = max({prw, prb}) + max({pcb + grid[i][j],
                // pcw});

                volatile int dummy = 0;
            }
        }

        ll rv = 0;
        for (auto i = 0; i < m; ++i)
            for (auto j = 0; j < n; ++j)
                for (auto k = 0; k < 2; ++k)
                    rv = max({rv, dpw[i][j], dpb[i][j]});

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
