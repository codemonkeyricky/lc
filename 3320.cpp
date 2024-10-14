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

class Solution {

  public:
    int countWinningSequences(const string& s) {
        int rv = 0, sz = s.size(), mod = 1000000007;
        /* can get away caching the most recent 2 values */
        long long dp[2][2001][3] = {};
        dp[0][1000][0] = 1;
        /* iterate through string */
        for (int i = 0; i < sz; ++i) {
            int a = s[i] == 'F' ? 2 : s[i] == 'E' ? 1 : 0;
            /* iterate through summons */
            for (int b = 0; b < 3; ++b) {
                // F > E, E > W, W > F
                int pt = a == b             ? 0
                         : a == 0 && b == 2 ? -1
                         : b == 0 && a == 2 ? 1
                         : a > b            ? -1
                                            : 1;
                /*
                 * iterate through scores
                 * normalize to 1000
                 */
                for (int j = 1000 - i; j < 1001 + i; ++j)
                    dp[!(i % 2)][j + pt][b] =
                        (dp[i % 2][j][0] + dp[i % 2][j][1] + dp[i % 2][j][2] -
                         /* 
                          * Bob doesn't repeat
                          * Exception when i == 0 as there's no previous.
                          */
                         (i == 0 ? 0 : dp[i % 2][j][b])) %
                        mod;
            }
        }
        for (int j = 1001; j < 1001 + sz; ++j)
            rv = (dp[sz % 2][j][0] + dp[sz % 2][j][1] + dp[sz % 2][j][2] + rv) %
                 mod;
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
