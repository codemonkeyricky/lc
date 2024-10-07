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

    vector<int> prefix(string& s, string& pattern) {
        vector<int> left(s.size());
        vector<int> lps(pattern.size());
        int l = 0;
        for (auto i = 1; i < pattern.size(); ++i) {
            if (pattern[i] == pattern[l]) {
                lps[i] = ++l;
            } else {
                if (l)
                    l = lps[l - 1];
                else
                    lps[i] = 0;
            }
        }

        for (auto i = 0, j = 0; i < s.size();) {
            if (s[i] == pattern[j]) {
                left[i++] = ++j;
            }

            if (j == pattern.size())
                j = lps[j - 1];
            else if (pattern[j] != s[i]) {
                if (j != 0)
                    j = lps[j - 1];
                else
                    i = i + 1;
            }
        }
        return left;
    }

  public:
    int minStartingIndex(string s, string pattern) {

        auto left = prefix(s, pattern);

        reverse(pattern.begin(), pattern.end());
        reverse(s.begin(), s.end());

        auto right = prefix(s, pattern);
        reverse(right.begin(), right.end());

        for (auto i = 0; i < s.size(); ++i) {

            if (left[i] == pattern.size())
                return i + 1 - left[i];
            else if (left[i] == pattern.size() - 1)
                return i + left[i];

            int l = i ? left[i - 1] : 0;
            int r = i < s.size() - 1 ? right[i + 1] : 0;

            if (l < pattern.size() && r < pattern.size() &&
                l + r >= pattern.size() - 1)
                return i - (i ? left[i - 1] : 0);
        }

        return -1;
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.minStartingIndex("ede", "d");
    cout << r << endl;

    r = sol.minStartingIndex("efeff", "fe");
    cout << r << endl;

    r = sol.minStartingIndex("ccbb", "bc");
    cout << r << endl;

    r = sol.minStartingIndex("dde", "d");
    cout << r << endl;

    r = sol.minStartingIndex("abcd", "dba");
    cout << r << endl;

    r = sol.minStartingIndex("ababbababa", "bacaba");
    cout << r << endl;

    r = sol.minStartingIndex("abcdefg", "bcdffg");
    cout << r << endl;
}
