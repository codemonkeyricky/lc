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

        ///< max_sum for with k black
        vector<vector<ll>> p(m, vector<ll>(m));
        vector<vector<ll>> pp(m, vector<ll>(m));
        vector<vector<ll>> c(m, vector<ll>(m));

        /* base case - nothing. Nothing to left of column 0 */
        vector<long long> prev_sum(m);

        /* iterate through all columns */
        for (auto j = 1; j < n; ++j) {

            vector<long long> sum(m);
            long long curr = 0;

            /* find sum at every row */
            for (auto k = 0; k < m; ++k) {
                curr += grid[k][j];
                sum[k] = curr;
            }

            /* iterate through all rows */

            /* consider pp */
            for (auto b = 0; b <= m; ++b) {
                for (auto pb = 0; pb <= m; ++pb) {
                    c[b][pb] =
                        prev_sum[max(b, pb)] ///< sum of elements in the middle
                        + grid[pb][j] + grid[pb][j]  ///< bottom of pp
                        + grid[pb][j] + grid[pb][j]; ///< bottom of c
                }
            }

            /* consider p */
            for (auto b = 0; b <= m; ++b) {
                for (auto pb = 0; pb <= m; ++pb) {
                    c[b][pb] =
                        prev_sum[max(b, pb)] ///< sum of elements in the middle
                        + grid[pb][j] + grid[pb][j]  ///< bottom of pp
                        + grid[pb][j] + grid[pb][j]; ///< bottom of c
                }
            }
        }

        ll rv = 0;
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
