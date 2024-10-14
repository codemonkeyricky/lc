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
    string longestPalindrome(string s) {
        int n = s.size();

        vvi dp(n, vi(n));

        /* base case - palindrome of length 1 or 2 */

        for (auto j = 0; j < n; ++j) {
            for (auto i = j - 1; i <= j; ++i) {
                if (i >= 0) {
                    if (i == j)
                        dp[i][j] = 1;
                    else if (s[i] == s[j])
                        dp[i][j] = 2;
                }
            }
        }

        for (auto j = 0; j < n; ++j) {
            for (auto i = 0; i + 1 < j; ++i) {
                if (s[i] == s[j] && dp[i + 1][j - 1]) {
                    dp[i][j] = 2 + dp[i + 1][j - 1];
                }
            }
        }

        array<int, 2> rv = {};
        int longest = 0;
        for (auto j = 0; j < n; ++j) {
            for (auto i = 0; i <= j; ++i) {
                if (dp[i][j] > longest) {
                    longest = dp[i][j];
                    rv = {i, j};
                }
            }
        }
        return s.substr(rv[0], rv[1] - rv[0] + 1);
    }
};

int main() {
    Solution sol;
    string r;

    r = sol.longestPalindrome("aacabdkacaa");
    cout << r << endl;

    r = sol.longestPalindrome("ccc");
    cout << r << endl;

    r = sol.longestPalindrome("cbbd");
    cout << r << endl;

    r = sol.longestPalindrome("babad");
    cout << r << endl;
}
