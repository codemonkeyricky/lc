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

    struct rect {
        int x;
        int y;
        int w;
        int h;
    };

    bool in_range(int v, int mmin, int mmax) { return v >= mmin && v <= mmax; }

    bool overlap(rect& A, rect& B) {
        bool x_overlap =
            in_range(A.x, B.x, B.x + B.w) || in_range(B.x, A.x, A.x + A.w);

        bool y_overlap =
            in_range(A.y, B.y, B.y + B.h) || in_range(B.y, A.y, A.y + A.h);

        return x_overlap && y_overlap;
    }

    bool fit(int m, int n, array<array<int, 2>, 3>& pts,
             array<array<int, 2>, 3>& boxes) {

        for (auto i = 0; i < 3; ++i) {
            if (pts[i][0] + boxes[i][0] > m)
                return false;
            if (pts[i][1] + boxes[i][1] > n)
                return false;
        }
        return true;
    }

    int count(vector<vector<int>>& g, array<rect, 3>& boxes) {
        int rv = 0;
        int m = g.size(), n = g[0].size();
        for (auto& b : boxes) {
            for (auto i = b.x; i < b.x + b.w; ++i) {
                for (auto j = b.y; j < b.y + b.h; ++j) {
                    rv += g[i][j];
                }
            }
        }
        return rv;
    }

    bool cover_all(vector<vector<int>>& g, vector<array<int, 2>>& pts,
                   array<array<int, 2>, 3>& boxes) {

        /* attempt all origins for all boxes */
        int n = boxes.size();
        for (auto i = 0; i < n; ++i) {
            for (auto j = i + 1; j < n; ++j) {
                for (auto k = j + 1; k < n; ++k) {

                    rect r0 = {pts[i][0], pts[i][1], boxes[0][0], boxes[0][1]};
                    rect r1 = {pts[j][0], pts[j][1], boxes[1][0], boxes[1][1]};
                    rect r2 = {pts[k][0], pts[k][1], boxes[2][0], boxes[2][1]};

                    /* check all boxes fit */
                    if (fit(g.size(), g[0].size(),
                            array<array<int, 2>, 3>() = {pts[i], pts[j],
                                                         pts[k]},
                            boxes)) {

                        /* check boxes don't overlap */
                        if (!overlap(r0, r1) && overlap(r1, r2) &&
                            overlap(r0, r2)) {
                            if (all_ones ==
                                count(g, array<rect, 3>() = {r0, r1, r2}))
                                return true;
                        }
                    }
                }
            }
        }
        return false;
    }

    int all_ones = 0;

  public:
    int minimumSum(vector<vector<int>>& grid) {

        int m = grid.size();
        int n = grid[0].size();

        /* all possible box dimension */
        vector<array<int, 2>> box;
        for (auto i = 1; i <= m; ++i)
            for (auto j = 1; j <= n; ++j)
                box.push_back({i, j});

        /* all possible 3 box permutation */
        vector<array<array<int, 2>, 3>> boxes;
        for (auto i = 0; i < box.size(); ++i)
            for (auto j = i; j < box.size(); ++j)
                for (auto k = j; k < box.size(); ++k)
                    boxes.push_back({box[i], box[j], box[k]});

        /* all possible origins */
        vector<array<int, 2>> pts;
        for (auto i = 0; i < m; ++i)
            for (auto j = 0; j < n; ++j)
                pts.push_back({i, j});

        /* count all ones */
        for (auto i = 0; i < m; ++i)
            for (auto j = 0; j < n; ++j)
                all_ones += grid[i][j];

        int rv = m * n;
        for (auto& b : boxes) {
            if (cover_all(grid, pts, b)) {
                int area = 0;
                for (auto& bb : b)
                    area += bb[0] * bb[1];
                rv = min(rv, area);
            }
        }

        return rv;
    }
};

int main() {
    Solution sol;
    int r;

    cout << r << endl;
}
