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

using vll = vector<long long>;
using vvll = vector<vector<long long>>;

class Solution {
    using vi = vector<int>;
    using vvi = vector<vector<int>>;

    int tops_down(string& w1, string& w2, int i, int j) {

        /* TODO: memoize for dp */

        if (i >= w1.size() && j >= w2.size())
            return 0;

        int a = 1e9, b = 1e9, c = 1e9;

        if (i < w1.size() && j < w2.size()) {
            if (w1[i] == w2[j])
                a = tops_down(w1, w2, i + 1, j + 1);
            else
                a = tops_down(w1, w2, i + 1, j + 1) + 1;
        }

        if (i < w1.size())
            b = tops_down(w1, w2, i + 1, j) + 1;

        if (j < w2.size())
            c = tops_down(w1, w2, i, j + 1) + 1;

        return min({a, b, c});
    }

    int bottoms_up(string& w1, string& w2) {
        int m = w1.size(), n = w2.size();

        vvi dp(vvi(m + 1, vi(n + 1)));

        /* base case: dp[0][x] = x */

        for (auto j = 1; j <= n; ++j) {
            dp[0][j] = j;
        }

        /* base case: dp[x][0] = x */
        for (auto i = 1; i <= m; ++i) {
            dp[i][0] = i;
        }

        for (auto i = 1; i <= m; ++i) {
            for (auto j = 1; j <= n; ++j) {
                int a = 1e9, b = 1e9, c = 1e9;
                if (w1[i - 1] == w2[j - 1])
                    a = dp[i - 1][j - 1];
                else
                    a = dp[i - 1][j - 1] + 1;
                b = dp[i - 1][j] + 1;
                c = dp[i][j - 1] + 1;

                dp[i][j] = min({a, b, c});
            }
        }

        return dp[m][n];
    }

  public:
    int minDistance(string w1, string w2) {
        // return tops_down(w1, w2);
        return bottoms_up(w1, w2);
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.minDistance("intention", "execution");
    cout << r << endl;

    r = sol.minDistance("horse", "ros");
    cout << r << endl;
}
