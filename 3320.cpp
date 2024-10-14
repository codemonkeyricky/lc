#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
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
using vvvi = vector<vector<vector<int>>>;
using vll = vector<long long>;
using vvll = vector<vector<long long>>;
using vvvll = vector<vector<vector<long long>>>;
using ll = long long;

#define N 1001
#define S 2001
#define MS (S/2)
#define P 4

ll dp[N][S][P] = {};
class Solution {

    /*
     * dp[[k][s]
     * number of ways for bob to win for a given s at k
     */

    const int F = 0;
    const int W = 1;
    const int E = 2;
    const int MOD = 1e9 + 7;

    int dfs(string& alice, int k, int p, int s) {
        int n = alice.size();

        if (k < 0) {
            return s > 1000;
        }

        /* no way we can catch up with remaining moves - return 0*/
        if (s + k < 1000)
            return 0;

        /*
         * F > E
         * W > F
         * E > W
         */

        if (dp[k][s][p] == 0) {
            ll rv = 0;
            switch (alice[k]) {
            case 'F': {
                if (p != F) // same
                    rv = (rv + dfs(alice, k - 1, F, s)) % MOD;
                if (p != W) // wins
                    rv = (rv + dfs(alice, k - 1, W, s + 1)) % MOD;
                if (p != E) // loses
                    rv = (rv + dfs(alice, k - 1, E, s - 1)) % MOD;

            } break;
            case 'W': {
                if (p != F) // loses
                    rv = (rv + dfs(alice, k - 1, F, s - 1)) % MOD;
                if (p != W) // same
                    rv = (rv + dfs(alice, k - 1, W, s)) % MOD;
                if (p != E) // wins
                    rv = (rv + dfs(alice, k - 1, E, s + 1)) % MOD;
            } break;
            case 'E': {
                if (p != F) // wins
                    rv = (rv + dfs(alice, k - 1, F, s + 1)) % MOD;
                if (p != W) // loses
                    rv = (rv + dfs(alice, k - 1, W, s - 1)) % MOD;
                if (p != E) // same
                    rv = (rv + dfs(alice, k - 1, E, s)) % MOD;
            } break;
            }
            dp[k][s][p] = rv + 1;
        }

        return dp[k][s][p] - 1;
    }

  public:
    int countWinningSequences(string alice) {

        memset(dp, 0, sizeof(dp));

        int n = alice.size();

        /* base case */

        for (auto s = N; s < S; ++s) {
            for (auto p = 0; p < 3; ++p) {
                dp[0][s][p] = 1;
            }
        }

        for (auto k = 1; k < n + 1; ++k) {
            for (auto s = 0; s < S; ++s) {
                for (auto p = 0; p < 3; ++p) {
                    if (alice[k - 1] == 'F') {
                        ll rv = 0;
                        if (p != F)
                            rv = (rv + dp[k - 1][s + 0][F]) % MOD;
                        if (p != W)
                            rv = (rv + dp[k - 1][s + 1][W]) % MOD;
                        if (p != E)
                            rv = (rv + dp[k - 1][s - 1][E]) % MOD;
                        dp[k][s][p] = rv;
                    } else if (alice[k] == 'W') {
                        ll rv = 0;
                        if (p != F)
                            rv = (rv + dp[k - 1][s - 1][F]) % MOD;
                        if (p != W)
                            rv = (rv + dp[k - 1][s + 0][W]) % MOD;
                        if (p != E)
                            rv = (rv + dp[k - 1][s + 1][E]) % MOD;
                        dp[k][s][p] = rv;
                    } else if (alice[k] == 'E') {
                        ll rv = 0;
                        if (p != F)
                            rv = (rv + dp[k - 1][s + 1][F]) % MOD;
                        if (p != W)
                            rv = (rv + dp[k - 1][s - 1][W]) % MOD;
                        if (p != E)
                            rv = (rv + dp[k - 1][s + 0][E]) % MOD;
                        dp[k][s][p] = rv;
                    }
                }
            }
        }

        // return dfs(alice, n - 1, 3, 1000);

        ll rv = 0;
        for (auto i = 0; i < 3; ++i)
            rv = (rv + dp[n][MS][i]) % MOD;

        return rv;
    }
};

int main() {
    Solution sol;
    int r;

    // r = sol.countWinningSequences("FWEFW");
    // cout << r << endl;

    r = sol.countWinningSequences("FFF");
    cout << r << endl;
}
