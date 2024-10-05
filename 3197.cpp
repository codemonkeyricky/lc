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

    bool overlap(rect& r1, rect& r2) {

        // Check if one rectangle is to the left of the other
        if (r1.x + r1.w <= r2.x || r2.x + r2.w <= r1.x)
            return 0;

        // Check if one rectangle is above the other
        if (r1.y + r1.h <= r2.y || r2.y + r2.h <= r1.y)
            return 0;

        // If none of the above, they overlap
        return 1;
    }

    bool fit(int m, int n, array<rect, 3>& rects) {
        for (auto& r : rects) {
            if (r.x + r.w > n)
                return false;
            if (r.y + r.h > m)
                return false;
        }
        return true;
    }

    int count(vector<vector<int>>& g, array<rect, 3>& boxes) {
        int rv = 0;
        int m = g.size(), n = g[0].size();
        for (auto& b : boxes) {
            for (auto i = b.y; i < b.y + b.h; ++i) {
                for (auto j = b.x; j < b.x + b.w; ++j) {
                    rv += g[i][j];
                }
            }
        }
        return rv;
    }

    bool cover_all(vector<vector<int>>& g, vector<array<int, 2>>& pts,
                   array<array<int, 2>, 3>& boxes) {

        /* attempt all origins for all boxes */
        int n = pts.size();
        for (auto i = 0; i < n; ++i) {
            for (auto j = 0; j < n; ++j) {
                for (auto k = 0; k < n; ++k) {
                    if (i != j && j != k && i != k) {

                        rect r0 = {pts[i][0], pts[i][1], boxes[0][0],
                                   boxes[0][1]};
                        rect r1 = {pts[j][0], pts[j][1], boxes[1][0],
                                   boxes[1][1]};
                        rect r2 = {pts[k][0], pts[k][1], boxes[2][0],
                                   boxes[2][1]};

                        /* check all boxes fit */
                        if (fit(g.size(), g[0].size(),
                                array<rect, 3>() = {r0, r1, r2})) {

                            auto o1 = overlap(r0, r1);
                            auto o2 = overlap(r1, r2);
                            auto o3 = overlap(r0, r2);

                            /* check boxes don't overlap */
                            if (!o1 && !o2 && !o3) {
                                if (all_ones ==
                                    count(g, array<rect, 3>() = {r0, r1, r2}))
                                    return true;
                            }
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
        for (auto w = 1; w <= n; ++w)
            for (auto h = 1; h <= m; ++h)
                box.push_back({w, h});

        /* all possible 3 box permutation */
        vector<array<array<int, 2>, 3>> boxes;
        for (auto i = 0; i < box.size(); ++i)
            for (auto j = 0; j < box.size(); ++j)
                for (auto k = 0; k < box.size(); ++k)
                    if (box[i][0] * box[i][1] + box[j][0] * box[j][1] +
                            box[k][0] * box[k][1] <=
                        m * n) {
                        /* make sure sum of boxes <= m * n */
                        boxes.push_back({box[i], box[j], box[k]});
                    }

        /* all possible origins */
        vector<array<int, 2>> pts;
        for (auto x = 0; x < n; ++x)
            for (auto y = 0; y < m; ++y)
                pts.push_back({x, y});

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

    r = sol.minimumSum(vector<vector<int>>() = {{0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0},
                                                {0, 0, 0, 1, 0},
                                                {1, 1, 0, 0, 0}});
    cout << r << endl;

    r = sol.minimumSum(vector<vector<int>>() = {{1, 0, 1}, {1, 1, 1}});
    cout << r << endl;
}
