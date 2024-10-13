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
    bool findSafeWalk(vector<vector<int>>& grid, int health) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> visited(m, vector<int>(n));

        queue<array<int, 3>> q;
        q.push({0, 0, health - grid[0][0]});
        visited[0][0] = health - grid[0][0];
        vector<int> offset = {0, 1, 0, -1, 0};
        while (q.size()) {
            auto [i, j, h] = q.front();
            q.pop();

            if (i == m - 1 && j == n - 1)
                return true;

            for (auto k = 0; k < 4; ++k) {
                auto ni = i + offset[k + 0];
                auto nj = j + offset[k + 1];

                if (ni >= 0 && ni < m && nj >= 0 && nj < n) {
                    if (h - grid[ni][nj] > 0)
                        if (h - grid[ni][nj] > visited[ni][nj]) {

                            q.push({ni, nj, h - grid[ni][nj]});
                            visited[ni][nj] = h - grid[ni][nj];
                        }
                }
            }
        }
        return false;
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.findSafeWalk(
        vector<vector<int>>() = {{0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0},
                                 {1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1},
                                 {0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0},
                                 {0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1},
                                 {1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1},
                                 {1, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1},
                                 {0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0},
                                 {0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1},
                                 {1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1},
                                 {0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1},
                                 {0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0},
                                 {1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 1},
                                 {0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                                 {1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1},
                                 {1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 0},
                                 {1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0},
                                 {0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
                                 {1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0},
                                 {1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0},
                                 {0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0},
                                 {1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1},
                                 {1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0},
                                 {1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1},
                                 {1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1},
                                 {1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1},
                                 {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1}},
        8);
    cout << r << endl;

    r = sol.findSafeWalk(vector<vector<int>>() =
                             {
                                 {0},
                                 {1},
                                 {0},
                                 {0},
                             },
                         2);
    cout << r << endl;

    r = sol.findSafeWalk(vector<vector<int>>() =
                             {
                                 {0, 0},
                                 {1, 1},
                             },
                         1);
    cout << r << endl;

    r = sol.findSafeWalk(vector<vector<int>>() = {{0, 1, 1, 0, 0, 0},
                                                  {1, 0, 1, 0, 0, 0},
                                                  {0, 1, 1, 1, 0, 1},
                                                  {0, 0, 1, 0, 1, 0}},
                         3);
    cout << r << endl;
}
