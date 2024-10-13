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

    int comb[1001][1001] = {}, dp[1001][1001] = {}, mod = 1000000007;
class Solution {
    long long modPow(int x, int y, int m) {
        if (y == 0)
            return 1;
        long long p = modPow(x, y / 2, m) % m;
        p = (p * p) % m;
        return y % 2 ? (p * x) % m : p;
    }

  public:
    int numberOfWays(int n, int x, int y) {
        if (comb[0][0] == 0) {
            comb[0][0] = dp[0][0] = 1;
            for (int n = 1; n < 1001; ++n) {
                comb[n][0] = 1;
                for (long long x = 1; x <= n; ++x) {
                    comb[n][x] = (comb[n - 1][x - 1] + comb[n - 1][x]) % mod;
                    dp[n][x] = x * (dp[n - 1][x - 1] + dp[n - 1][x]) % mod;
                }
            }
        }
        long long res = 0;
        for (int st = 1; st <= min(n, x); ++st)
            res = (res +
                   modPow(y, st, mod) * comb[x][st] % mod * dp[n][st] % mod) %
                  mod;
        return res;
    }
};

int main() {
    Solution sol;
    int r;

    // r = sol.numberOfWays(1, 2, 3);
    // cout << r << endl;

    r = sol.numberOfWays(3, 3, 4);
    cout << r << endl;

    r = sol.numberOfWays(3, 2, 4);
    cout << r << endl;

    r = sol.numberOfWays(2, 2, 4);
    cout << r << endl;

    r = sol.numberOfWays(1, 1, 4);
    cout << r << endl;

    // r = sol.numberOfWays(3, 3, 4);
    // cout << r << endl;

    // r = sol.numberOfWays(5, 2, 1);
    // cout << r << endl;
}
