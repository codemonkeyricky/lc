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
    void dfs(vector<vector<char>>& grid, int i, int j) {

        int m = grid.size();
        int n = grid[0].size();

        if (grid[i][j] == '2' || grid[i][j] == '0')
            return;

        grid[i][j] = '2';

        vector<int> offset = {0, 1, 0, -1, 0};
        for (auto k = 0; k < 4; ++k) {
            auto ni = i + offset[k + 0];
            auto nj = j + offset[k + 1];
            if (ni >= 0 && ni < m && nj >= 0 && nj < n)
                dfs(grid, ni, nj);
        }
    }

  public:
    int numIslands(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        int rv = 0;
        for (auto i = 0; i < m; i++) {
            for (auto j = 0; j < n; j++) {
                if (grid[i][j] == '1') {
                    dfs(grid, i, j);
                    ++rv;
                }
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
