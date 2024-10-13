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
    int coinChange(vi& coins, int amount) {

        int n = coins.size();

        vi dp(amount + 1, 1e9);

        /* base */
        dp[0] = 0;
        for (auto i = 0; i <= amount; ++i) {
            for (auto j = 0; j < coins.size(); ++j) {
                if (i - coins[j] >= 0) {
                    dp[i] = min(1 + dp[i - coins[j]], dp[i]);
                }
            }
        }
        return dp[amount] == 1e9 ? -1 : dp[amount];
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.coinChange(vector<int>() = {1, 2, 5}, 11);
    cout << r << endl;
}
