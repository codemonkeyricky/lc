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
  public:
    int minPathSum(vector<vector<int>>& g) {

        int m = g.size();
        int n = g[0].size();

        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 1e9));
        dp[0][1] = 0;
        for (auto i = 0; i < m; ++i) {
            for (auto j = 0; j < n; ++j) {
                dp[i + 1][j + 1] = min(dp[i][j + 1], dp[i + 1][j]) + g[i][j];
            }
        }

        return dp[m][n];
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.minPathSum(vector<vector<int>>() = {{1, 2, 3}, {4, 5, 6}});
    cout << r << endl;

    r = sol.minPathSum(
        vector<vector<int>>() = {{1, 3, 1}, {1, 5, 1}, {4, 2, 1}});
    cout << r << endl;
}
