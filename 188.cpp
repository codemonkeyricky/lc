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
#include <climits>

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
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();

        // Solve special cases
        if (n <= 0 || k <= 0) {
            return 0;
        }

        if (k * 2 >= n) {
            int res = 0;
            for (int i = 1; i < n; i++) {
                res += max(0, prices[i] - prices[i - 1]);
            }
            return res;
        }

        // dp[i][used_k][is_hold] = balance
        // is_hold: 0 not_hold, 1 hold
        vector<vector<vector<int>>> dp(
            n, vector<vector<int>>(k + 1, vector<int>(2, 0)));

        // initialize the array with -inf
        // we use INT_MIN/2 here to prevent overflow
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= k; j++) {
                dp[i][j][0] = INT_MIN / 2;
                dp[i][j][1] = INT_MIN / 2;
            }
        }

        // set starting value
        dp[0][0][0] = 0;
        dp[0][1][1] = -prices[0];

        // fill the array
        for (int i = 1; i < n; i++) {
            for (int j = 0; j <= k; j++) {
                // transition equation
                dp[i][j][0] = max(dp[i - 1][j][0], dp[i - 1][j][1] + prices[i]);
                // you can't hold stock without any transaction
                if (j > 0) {
                    dp[i][j][1] =
                        max(dp[i - 1][j][1], dp[i - 1][j - 1][0] - prices[i]);
                }
            }
        }

        int res = 0;
        for (int j = 0; j <= k; j++) {
            res = max(res, dp[n - 1][j][0]);
        }

        return res;
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.maxProfit(2, vector<int>() = {1, 2, 4, 2, 5, 7, 2, 4, 9, 0});
    cout << r << endl;

    r = sol.maxProfit(2, vector<int>() = {2, 4, 1});
    cout << r << endl;

    r = sol.maxProfit(2, vector<int>() = {3, 2, 6, 5, 0, 3});
    cout << r << endl;
}
