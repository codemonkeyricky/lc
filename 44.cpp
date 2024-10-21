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
        vector<vector<bool>> dp(s.size() + 1, vector(p.size() + 1, false));
        dp[0][0] = true;
        for (int j = 0; j < p.size() && p[j] == '*'; ++j) {
            dp[0][j + 1] = true;
        }

        for (int i = 1; i <= s.size(); ++i) {
            for (int j = 1; j <= p.size(); ++j) {
                if (p[j - 1] == '*') {
                    /* 
                     * first case: * has been matched one or more times 
                     * second case: * is being matched the first time
                     */
                    dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
                } else {
                    dp[i][j] = (s[i - 1] == p[j - 1] || p[j - 1] == '?') &&
                               dp[i - 1][j - 1];
                }
            }
        }

        return dp[s.size()][p.size()];
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
