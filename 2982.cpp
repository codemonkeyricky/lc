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

class Solution {

  public:
    int maximumLength(string s) {
        int n = s.size();

        vector<map<int, int>> dp(26);

        for (auto i = 0, j = 1; j <= n; ++j) {
            if (j < n && s[j - 1] == s[j])
                ;
            else {
                ++dp[s[j - 1] - 'a'][j - i];
                i = j;
            }
        }

        int rv = 0;
        for (auto k = 0; k < 26; ++k) {
            map<int, int> len;
            for (auto& d : dp[k]) {
                // d.first = string length
                // d.second = number of strings with this lengh
                len[d.first] += d.second;
                if (d.first >= 2)
                    len[d.first - 1] += 2 * d.second;
                if (d.first >= 3)
                    len[d.first - 2] += 3 * d.second;
            }
            for (auto& l : len)
                if (l.second >= 3)
                    rv = max(rv, l.first);
        }

        return rv == 0 ? -1 : rv;
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.maximumLength("iiiiifffffffoooookkkfffffffnnxxxxxx");
    cout << r << endl;

    r = sol.maximumLength("aaa");
    cout << r << endl;

    r = sol.maximumLength("abc");
    cout << r << endl;

    r = sol.maximumLength("aaaa");
    cout << r << endl;
}