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
    int dfs(vector<int>& prices, int j) {
        if (j <= 0)
            return 0;

        int rv = dfs(prices, j - 1);
        for (int i = j - 1; i >= 0; --i) {
            if (prices[j] > prices[i])
                rv = max(rv, prices[j] - prices[i] + dfs(prices, i - 2));
        }
        return rv;
    }

  public:
    int maxProfit(vector<int>& p) {
        int n = p.size();
        vector<int> dp(n + 1);

        for (auto j = 1; j < n + 1; ++j) {
            dp[j] = dp[j - 1];
            for (auto i = 1; i < j; ++i) {
                if (p[i - 1] < p[j - 1]) {
                    dp[j] = max(dp[j], p[j - 1] - p[i - 1] + dp[i - 2]);
                }
            }
        }

        return dp[n];
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.maxProfit(vector<int>() = {1, 3, 4, 0, 4});
    cout << r << endl;
}
