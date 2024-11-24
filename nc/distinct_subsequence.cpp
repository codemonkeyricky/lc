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

    int dfs(string& s, string& t, int i, int j) {
        /* all of t matched */
        if (j >= t.size())
            return 1;
        /* ran out of s */
        if (i >= s.size())
            return 0;

        if (dp[i][j] == 0) {

            int a = 0, b = 0;
            a = dfs(s, t, i + 1, j);
            if (s[i] == t[j])
                b = dfs(s, t, i + 1, j + 1);

            dp[i][j] = a + b + 1;
        }

        return dp[i][j] - 1;
    }

    vector<vector<int>> dp;

  public:
    int numDistinct(string s, string t) {
        int m = s.size(), n = t.size();
        dp = vector<vector<int>>(m + 1, vector<int>(n + 1));

        // return dfs(s, t, 0, 0);

        /* any j of size 0 is true */
        for (auto i = 0; i < m; ++i) {
            dp[i][0] = 1;
        }

        for (auto i = 1; i <= m; ++i) {
            for (auto j = 1; j <= n; ++j) {
                dp[i][j] += dp[i - 1][j];
                if (s[i - 1] == t[j - 1])
                    dp[i][j] += dp[i - 1][j - 1];
            }
        }

        return dp[m][n];
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.numDistinct("caaat", "cat");
    cout << r << endl;
}
