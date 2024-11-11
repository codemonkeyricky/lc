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

    int minus_one(string& s) {
        int n = s.size();
        int borrow = 0;
        for (int i = n - 1; i >= 0; --i) {
            if (s[i] == '1') {
                s[i] = '0';
                return 0;
            } else {
                s[i] = '1';
                borrow = true;
            }
        }
        return borrow == false;
    }

    /* equal or less */
    int dfs(string& s, int k, int ones, bool ceiling, string curr) {

        int n = s.size();

        /* base case */
        if (k >= n) {
            if (ones == 0) {
                // cout << curr << endl;

                return 1;
            } else
                return 0;
        }

        int a = 0, b = 0;

        if (ceiling) {
            /* must follow s[k] */
            if (s[k] == '1' && ones) {
                a = dfs(s, k + 1, ones - 1, true, curr + '1');
                b = dfs(s, k + 1, ones, false, curr + '0');
            } else {
                b = dfs(s, k + 1, ones, true, curr + '0');
            }
        } else {
            if (ones) {
                a = dfs(s, k + 1, ones - 1, false, curr + '1');
            }
            b = dfs(s, k + 1, ones, false, curr + '0');
        }

        return a + b;
    }

    vector<int> lookup; // bits to number of ops to 1

  public:
    int countKReducibleNumbers(string s, int k) {

        minus_one(s);

        constexpr int N = 800;

        /* find set of bit count can get to 1 at most k moves */
        lookup = vector<int>(N + 1);
        /* TODO */
        for (auto i = 1; i <= N; ++i) {
            int ii = i, k = 1;
            while (ii != 1) {
                /* count number of bits */
                int bits = 0;
                for (; ii; ++bits)
                    ii &= ii - 1;
                ii = bits;
                ++k;
            }
            lookup[i] = k;
        }

        vector<int> check;
        /* TODO */
        for (auto i = 1; i < N; ++i) {
            if (lookup[i] <= k)
                check.push_back(i);
        }

        long long rv = 0;
        for (auto& k : check) {
            rv = rv + dfs(s, 0, k, true, "");
        }

        return rv;
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.countKReducibleNumbers("10010", 2);
    cout << r << endl;

    // r = sol.countKReducibleNumbers("10", 2);
    // cout << r << endl;

    // r = sol.countKReducibleNumbers("1000", 2);
    // cout << r << endl;

    // r = sol.countKReducibleNumbers("111", 1);
    // cout << r << endl;
}