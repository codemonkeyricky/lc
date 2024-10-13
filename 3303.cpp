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
    int minStartingIndex(string s, string p) {
        int ps = p.size(), ss = s.size();
        auto zr = z_function(p + s);
        auto zl =
            z_function(string(rbegin(p), rend(p)) + string(rbegin(s), rend(s)));
        for (int i = 0; i <= ss - ps; ++i)
            if (zr[ps + i] + zl[ss - i] >= ps - 1)
                return i;
        return -1;
    }
    vector<int> z_function(const string& s) {
        vector<int> z(s.size());
        int l = 0, r = 0;
        for (int i = 1; i < s.size(); i++) {
            if (i < r)
                z[i] = min(r - i, z[i - l]);
            while (i + z[i] < s.size() && s[z[i]] == s[i + z[i]])
                z[i]++;
            if (i + z[i] > r) {
                l = i;
                r = i + z[i];
            }
        }
        return z;
    }
};

int main() {
    Solution sol;
    int r;

    // r = sol.minStartingIndex("ffggf", "gg");
    // cout << r << endl;

    // r = sol.minStartingIndex("ede", "d");
    // cout << r << endl;

    // r = sol.minStartingIndex("efeff", "fe");
    // cout << r << endl;

    // r = sol.minStartingIndex("ccbb", "bc");
    // cout << r << endl;

    // r = sol.minStartingIndex("dde", "d");
    // cout << r << endl;

    // r = sol.minStartingIndex("abcd", "dba");
    // cout << r << endl;

    r = sol.minStartingIndex("ababbababa", "bacaba");
    cout << r << endl;

    r = sol.minStartingIndex("abcdefg", "bcdffg");
    cout << r << endl;
}
