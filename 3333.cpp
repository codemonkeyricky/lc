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
    const int MOD = 1e9 + 7;

    vector<vector<int>> dp;

  public:
    int possibleStringCount(string word, int kk) {
        vector<int> cnt;

        for (auto i = 1, c = 1; i <= word.size(); ++i) {
            if (i < word.size() && word[i - 1] == word[i]) {
                ++c;
            } else {
                cnt.push_back(c);
                c = 1;
            }
        }

        vector<long long> prefix(cnt.size());
        long long m = 1;
        for (int i = 0; i < cnt.size(); ++i) {
            m = (m * cnt[i]) % MOD;
            prefix[i] = m;
        }

        dp = vector<vector<int>>(cnt.size(), vector<int>(kk + 1));

        m = 1;
        for (int i = 0; i < cnt.size(); ++i) {
            m = (m * cnt[i]) % MOD;
            dp[i][0] = m;
        }

        /* base case */
        for (auto i = 1; i <= cnt[0] && i <= kk; ++i)
            dp[0][i] = cnt[0] - i + 1;

        for (auto i = 1; i < cnt.size(); ++i) {
            long long sum = ((long long)dp[i - 1][0] * cnt[i]) % MOD;
            for (auto k = 1; k <= kk; ++k) {

                if (k <= i + 1) {
                    dp[i][k] = sum;
                } else {
                    sum -= dp[i - 1][max(0, k - cnt[i] - 1)];
                    if (sum < 0)
                        sum += MOD;
                    sum = (sum + dp[i - 1][k - 1]) % MOD;
                    dp[i][k] = sum;
                }
            }
        }

        return dp[cnt.size() - 1][kk];
    }
};

int main() {
    Solution sol;
    int r;

    /*
     * dp[0][1] = 3
     * dp[0][2] = 2
     */

    r = sol.possibleStringCount("ggggggggaaaaallsssssaaaaaaaaaiiqqqqqqqqqqbbbbb"
                                "bbvvfffffjjjjeeeeeefffmmiiiix",
                                34);
    cout << r << endl;

    r = sol.possibleStringCount("aadddf", 3);
    cout << r << endl;

    // r = sol.possibleStringCount("bb", 1);
    // cout << r << endl;

    r = sol.possibleStringCount("aaabbb", 3);
    cout << r << endl;

    // r = sol.possibleStringCount("aabbccdd", 8);
    // cout << r << endl;

    // r = sol.possibleStringCount("aabbccdd", 7);
    // cout << r << endl;
}
