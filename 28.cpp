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

    int rabin_karp(string& haystack, string& needle) {

        static constexpr int MOD = 1000000007;
        static constexpr int MUL = 27;

        /* Intuition:
         * Assume a number 12345, and we want to find if 45 exists.
         * 1
         * 1 * 10 + 2 = 12
         * 12 * 10 + 3 - 1 * 100 = 23
         * 23 * 10 + 4 - 2 * 100 = 34
         * 34 * 10 + 5 - 3 * 100 = 45  <--- target found
         *
         * In the above example, the multiplier is 10 and power is 100
         */

        /* construct the needle hash */
        long hash = 0, power = 1;
        for (auto& c : needle) {
            /* add 1 because if a is 0 then hash of a = aa = aaa = ... */
            hash = (hash * MUL + c - 'a' + 1) % MOD;
            power = (power * MUL) % MOD;
        }

        /* perform rolling hash */

        long rolling = 0;
        for (auto i = 0; i < haystack.size(); ++i) {

            /* add new character */
            rolling = (rolling * MUL + haystack[i] - 'a' + 1) % MOD;

            /* remove old */
            if (i >= needle.size()) {
                rolling -= (haystack[i - needle.size()] - 'a' + 1) * power;
                while (rolling < 0)
                    rolling += MOD;
            }

            /* did we find target? */
            if (rolling == hash)
                return i - needle.size() + 1;
        }

        return -1;
    }

    // Compute lps
    vector<int> get_lps(string& pat) {

        int n = pat.size();
        vector<int> lps(n);

        int i = 1, j = 0;
        lps[0] = 0;
        while (i < n) {
            if (pat[i] == pat[j]) {
                lps[i++] = ++j;
            } else {
                if (j != 0) {
                    j = lps[j - 1];
                } else {
                    lps[i++] = 0;
                }
            }
        }

        return lps;
    }

    int kmp(string& s, string& p, vector<int>& lps) {
        int m = lps.size();
        int n = s.size();

        int i = 0, j = 0;
        while (n - i >= m - j) {

            /*
             * i points to haystack
             * j points to needle
             */

            if (p[j] == s[i]) {
                ++i, ++j;
            }

            if (j == m) {
                /* match found */
                return i - m;
            } else if (i < n && p[j] != s[i]) {
                if (j != 0) {
                    /* smart unwind */
                    j = lps[j - 1];
                } else {
                    /* cannot unwind anymore */
                    i = i + 1;
                }
            }
        }
        return -1;
    }

  public:
    int strStr(string haystack, string needle) {
#if 0
        return rabin_karp(haystack, needle);
#else
        auto lps = get_lps(needle);
        return kmp(haystack, needle, lps);
#endif
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.strStr("aaaaaaabaaa", "aaabaaa");
    cout << r << endl;

    r = sol.strStr("aaaaaaabc", "aaabc");
    cout << r << endl;

    r = sol.strStr("aaaaaaaaaaaabaa", "aaaabaa");
    cout << r << endl;

    r = sol.strStr("mississippi", "issip");
    cout << r << endl;

    r = sol.strStr("aba", "b");
    cout << r << endl;

    r = sol.strStr("aaa", "aa");
    cout << r << endl;

    r = sol.strStr("a", "a");
    cout << r << endl;

    r = sol.strStr("sadbutsad", "sad");
    cout << r << endl;
}
