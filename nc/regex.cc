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

// class Solution {
//   public:
//     bool isMatch(string s, string p) {

//         int sz = s.size() + 1;
//         int pz = p.size() + 1;

//         vector<vector<int>> dp(s.size() + 1, vector<int>(p.size() + 1));

//         /*
//          * dp[i][j] = s[0..i] matches up to p[0..j]
//          */

//         /* base case */
//         dp[0][0] = 1;

//         for (auto i = 1; i < sz; ++i) {
//             for (auto j = 1; j < pz; ++j) {
//                 auto ii = i - 1, jj = j - 1;
//                 if (s[i - 1] == p[j - 1] || p[j - 1] == '.') {
//                     /* i and j match - take result from i-1 and j-1 */
//                     dp[i][j] = dp[i - 1][j - 1];
//                     if (jj >= 2 && p[jj - 1] == '*') {
//                         /* if prev is *, can also skip */
//                         dp[i][j] |= dp[i - 1][j - 3];
//                     }
//                 } else if (p[jj] == '*') {
//                     /* p cannot start with '*' */

//                     /* does prev char match? */
//                     if (s[i - 1] == p[j - 2] || p[j - 2] == '.') {
//                         dp[i][j] |= dp[i - 1][j - 1];
//                     }

//                     /* ignore 'x*' */
//                     dp[i][j] |= dp[i][j - 2];
//                 }
//             }
//         }

//         return dp[sz - 1][pz - 1];
//     }
// };

class Solution {
    bool dfs(string& s, string& p, int i, int j) {
        if (i >= s.size() && j >= p.size())
            return true;
        // else if (j >= p.size())
        //     return false;
        // else if (i >= s.size())
        //     return false;

        int rv = 0;

        if (dp[i][j] == 0) {
            /* prioritize wildcard */
            if (j + 1 < p.size() && p[j + 1] == '*') {
                /* skip wildcard */
                rv |= dfs(s, p, i, j + 2);
                if (i < s.size() && (s[i] == p[j] || p[j] == '.')) {
                    /* match once */
                    rv |= dfs(s, p, i + 1, j + 2);
                    /* match multiple */
                    rv |= dfs(s, p, i + 1, j);
                }

            } else if (i < s.size() && (p[j] == '.' || s[i] == p[j])) {
                rv |= dfs(s, p, i + 1, j + 1);
            }

            dp[i][j] = rv + 1;
        }

        return dp[i][j] - 1;
    }

    vector<vector<int>> dp;

  public:
    bool isMatch(string s, string p) {
        dp = vector<vector<int>>(s.size() + 1, vector<int>(p.size() + 1));
        return dfs(s, p, 0, 0);
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.isMatch("aaaaaaaaaaaaaaaaaaab", "a*a*a*a*a*a*a*a*a*a*");
    cout << r << endl;

    r = sol.isMatch("a", "ab*");
    cout << r << endl;

    r = sol.isMatch("ab", ".*");
    cout << r << endl;

    r = sol.isMatch("a", "c*a");
    cout << r << endl;

    r = sol.isMatch("aaa", "ab*a");
    cout << r << endl;

    r = sol.isMatch("aa", "a*");
    cout << r << endl;
}
