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
    /* modulus */
    static constexpr int M = 1000000007;
    static constexpr int MUL = 27;

    int rabin_karp(string& haystack, string& needle) {

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
            hash = (hash * MUL + c - 'a' + 1) % M;
            power = (power * MUL) % M;
        }

        /* perform rolling hash */

        long rolling = 0;
        for (auto i = 0; i < haystack.size(); ++i) {

            /* add new character */
            rolling = (rolling * MUL + haystack[i] - 'a' + 1) % M;

            /* remove old */
            if (i >= needle.size()) {
                rolling -= (haystack[i - needle.size()] - 'a' + 1) * power;
                while (rolling < 0)
                    rolling += M;
            }

            /* did we find target? */
            if (rolling == hash)
                return i - needle.size() + 1;
        }

        return -1;
    }

    // Compute lps
    vector<int> get_lps(string& pat) {
        // Length of the previous longest prefix suffix
        int len = 0;

        int M = pat.size();
        vector<int> lps(M);

        // lps[0] is always 0
        lps[0] = 0;

        // loop calculates lps[i] for i = 1 to M-1
        int i = 1;
        while (i < M) {
            if (pat[i] == pat[len]) {
                len++;
                lps[i] = len;
                i++;
            } else // (pat[i] != pat[len])
            {
                if (len != 0) {
                    len = lps[len - 1];
                } else // if (len == 0)
                {
                    lps[i] = 0;
                    i++;
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
            if (p[j] == s[i]) {
                ++i, ++j;
            }

            if (j == m) {
                return i - m;
            } else if (i < n && p[j] != s[i]) {
                if (j != 0)
                    j = lps[j - 1];
                else
                    i = i + 1;
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


    r = sol.strStr("aba", "b");
    cout << r << endl;


    r = sol.strStr("aaa", "aa");
    cout << r << endl;

    r = sol.strStr("a", "a");
    cout << r << endl;

    r = sol.strStr("sadbutsad", "sad");
    cout << r << endl;
}
