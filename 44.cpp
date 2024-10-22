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

class Solution {
  public:
    bool isMatch(string s, string p) {

        int sz = s.size() + 1;
        int pz = p.size() + 1;

        vector<vector<int>> dp(sz + 1, vector<int>(pz));

        /*
         * dp[i][j] = s[0..i] matches up to p[0..j]
         */

        /* base case */
        dp[0][0] = 1;
        for (int j = 0; j < p.size() && p[j] == '*'; ++j) {
            dp[0][j + 1] = true;
        }

        for (auto i = 1; i < sz; ++i) {
            for (auto j = 1; j < pz; ++j) {
                if (i < sz && (s[i - 1] == p[j - 1] || p[j - 1] == '?')) {
                    /* i and j match - take result from i-1 and j-1? */
                    dp[i][j] = dp[i - 1][j - 1];
                } else if (p[j - 1] == '*') {
                    int a = 0, b = 0, c = 0;

                    // match many times
                    // if (i < sz)
                    a = dp[i - 1][j];

                    // match once
                    // if (i < sz)
                    b = dp[i - 1][j - 1];

                    // skip '*'
                    c = dp[i][j - 1];

                    dp[i][j] = max({a, b, c});
                }
            }
        }

        return dp[sz - 1][pz - 1];
    }
};

int main() {
    Solution sol;
    int r;

    // r = sol.isMatch("", "*");
    // cout << r << endl;

    r = sol.isMatch("a", "*a");
    cout << r << endl;

    r = sol.isMatch("adceb", "*a*b");
    cout << r << endl;

    r = sol.isMatch("adceb", "*a*b");
    cout << r << endl;

    // r = sol.isMatch("abcde", "*e");
    // cout << r << endl;

    // r = sol.isMatch("ab", "b*");
    // cout << r << endl;

    r = sol.isMatch("ab", "a*");
    cout << r << endl;

    r = sol.isMatch("a", "a");
    cout << r << endl;

    r = sol.isMatch("aaa", "a");
    cout << r << endl;

    r = sol.isMatch("aaa", "*");
    cout << r << endl;
}
