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

    int dfs(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        for (auto i = 0; i < m; ++i)
            for (auto j = 0; j < n; ++j)
                for (auto k = 1; k < m; ++m)
                    for (auto j = 0; j < n; ++j)
    }

  public:
    int minimumSum(vector<vector<int>>& grid) { dfs(grid); }
};

int main() {
    Solution sol;
    int r;

    cout << r << endl;
}
