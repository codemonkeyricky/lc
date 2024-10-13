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
using vvvi = vector<vector<vector<int>>>;
using vll = vector<long long>;
using vvll = vector<vector<long long>>;
using vvvll = vector<vector<vector<long long>>>;
using ll = long long;

class Solution {

    /*
     * dp[[k][score]
     * number of ways for bob to win for a given score at k
     */

    const int F = 0;
    const int W = 1;
    const int E = 2;
    const int MOD = 1e9 + 7;

    int dfs(string& s, int k, int p, int score) {
        int n = s.size();

        if (k < 0) {
            return score > 1000;
        }

        /* no way we can catch up with remaining moves - return 0*/
        if (score + k < 1000)
            return 0;

        /*
         * F > E
         * W > F
         * E > W
         */

        if (dp[k][score][p] == 0) {
            ll rv = 0;
            switch (s[k]) {
            case 'F': {
                if (p != F) // same
                    rv = (rv + dfs(s, k - 1, F, score)) % MOD;
                if (p != W) // wins
                    rv = (rv + dfs(s, k - 1, W, score + 1)) % MOD;
                if (p != E) // loses
                    rv = (rv + dfs(s, k - 1, E, score - 1)) % MOD;

            } break;
            case 'W': {
                if (p != F) // loses
                    rv = (rv + dfs(s, k - 1, F, score - 1)) % MOD;
                if (p != W) // same
                    rv = (rv + dfs(s, k - 1, W, score)) % MOD;
                if (p != E) // wins
                    rv = (rv + dfs(s, k - 1, E, score + 1)) % MOD;
            } break;
            case 'E': {
                if (p != F) // wins
                    rv = (rv + dfs(s, k - 1, F, score + 1)) % MOD;
                if (p != W) // loses
                    rv = (rv + dfs(s, k - 1, W, score - 1)) % MOD;
                if (p != E) // same
                    rv = (rv + dfs(s, k - 1, E, score)) % MOD;
            } break;
            }
            dp[k][score][p] = rv + 1;
        }

        return dp[k][score][p] - 1;
    }

    ll dp[1001][2001][4] = {};

  public:
    int countWinningSequences(string s) {
        int n = s.size();
        int rv = 0;

        // dp = vvvll(n + 1, vvll(n + 1001, vll(4)));
        return dfs(s, n - 1, 3, 1000);
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.countWinningSequences("FWEFW");
    cout << r << endl;

    r = sol.countWinningSequences("FFF");
    cout << r << endl;
}
