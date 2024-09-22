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
    int numberOfSubmatrices(vector<vector<char>>& grid) {
        int m = grid.size(), n = grid[0].size();
        int x = 0, y = 0;
        int rv = 0;
        vector<vector<array<int, 2>>> dp(m, vector<array<int, 2>>(n));
        for (auto i = 0; i < m; ++i) {
            array<int, 2> xy = {};
            for (auto j = 0; j < n; ++j) {
                if (grid[i][j] == 'X')
                    ++xy[0];
                else if (grid[i][j] == 'Y')
                    ++xy[1];

                array<int, 2> sub = {};
                if (i)
                    sub = dp[i - 1][j];
                
                sub[0] += xy[0];
                sub[1] += xy[1];

                dp[i][j] = sub;

                if (sub[0] && sub[0] == sub[1]) 
                    ++rv;
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