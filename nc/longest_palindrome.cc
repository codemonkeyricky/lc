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
        vector<vector<int>> dp(n, vector<int>(n));

        /* base case */
        string rv;
        rv += s[0];

        for (auto i = 0; i < n; ++i) {
            dp[i][i] = 1;
        }

        for (auto i = 0; i + 1 < n; ++i) {
            if (s[i] == s[i + 1]) {
                dp[i][i + 1] = 2;
                rv = s.substr(i, 2);
            }
        }

        for (auto j = 0; j < n; ++j) {
            for (auto i = 0; i + 1 < j; ++i) {
                if (s[i] == s[j] && dp[i + 1][j - 1]) {
                    dp[i][j] = dp[i + 1][j - 1] + 2;
                    if (dp[i][j] > rv.size()) {
                        rv = s.substr(i, j - i + 1);
                    }
                }
            }
        }
        return rv;
    }
};

int main() {
    Solution sol;
    string r;

    r = sol.longestPalindrome("aacabdkacaa");
    cout << r << endl;
}
