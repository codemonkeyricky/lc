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
using ll = long long;

class Solution {

    long long n_choose_k(long long n, long long k) {
        if (k == 0)
            return 1;
        return (n * n_choose_k(n - 1, k - 1)) / k;
    }

  public:
    int numberOfWays(int n, int x, int y) {
        vvi dp(n + 1, vi(x + 1));

        /* dp[n][x] is n performers in x stages */

        for (auto i = 1; i <= x; ++i)
            dp[0][i] = 1;

        for (auto nn = 1; nn <= n; ++nn) {
            /*
             * dp[nn][xx] adds a new performer to dp[nn-1][xx].
             * New performer can join any of the stages from 1 to xx.
             */
            for (auto xx = 1; xx <= x; ++xx) {
                dp[nn][xx] += dp[nn - 1][xx] * xx;
                volatile int dummy = 0;
            }
        }

        // ll rv = 0;
        // for (auto xx = 1; xx <= x; ++xx) {
        //     /* need to spread xx across x stages using nCk */
        //     rv = rv + dp[n][xx] * n_choose_k(x, xx); /* TODO: x choose xx */
        // }

        return dp[n][x] * y;
    }
};

int main() {
    Solution sol;
    int r;

    // r = sol.numberOfWays(3, 3, 4);
    // cout << r << endl;

    r = sol.numberOfWays(5, 2, 1);
    cout << r << endl;
}
