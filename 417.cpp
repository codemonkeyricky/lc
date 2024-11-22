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

void pvi(vector<int>& v) {

    for (auto& vv : v)
        cout << vv << ", ";
    cout << endl;
}

using vi = vector<int>;
using vvi = vector<vector<int>>;
using vll = vector<long long>;
using vvll = vector<vector<long long>>;

class Solution {

    void dfs(vector<vector<int>>& h, vector<vector<int>>& seen, int i, int j) {
        int m = h.size();
        int n = h[0].size();

        seen[i][j] = true;
        vector<int> offset = {0, -1, 0, 1, 0};
        for (auto k = 0; k < 4; ++k) {
            auto ni = i + offset[k + 0];
            auto nj = j + offset[k + 1];
            if (ni >= 0 && ni < m && nj >= 0 && nj < n && !seen[ni][nj]) {
                if (h[ni][nj] >= h[i][j])
                    dfs(h, seen, ni, nj);
            }
        }
    }

  public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& h) {
        int m = h.size();
        int n = h[0].size();
        vector<vector<int>> p(m, vector<int>(n)), a(m, vector<int>(n));

        for (auto i = 0; i < m; ++i) {
            /* pacific flows left to right */
            dfs(h, p, i, 0);
            /* atlantic flows right to left */
            dfs(h, a, i, n - 1);
        }

        for (auto j = 0; j < n; ++j) {
            /* pacific flows top down */
            dfs(h, p, 0, j);
            /* atlantic flows bottoms down */
            dfs(h, a, m - 1, j);
        }

        vector<vector<int>> rv;
        for (auto i = 0; i < m; ++i) {
            for (auto j = 0; j < n; ++j) {
                if (p[i][j] && a[i][j])
                    rv.push_back({i, j});
            }
        }
        return rv;
    }
};

int main() {
    Solution sol;
    int r;

    sol.pacificAtlantic(vector<vector<int>>() = {{1, 2, 2, 3, 5},
                                                 {3, 2, 3, 4, 4},
                                                 {2, 4, 5, 3, 1},
                                                 {6, 7, 1, 4, 5},
                                                 {5, 1, 1, 2, 4}});
}
