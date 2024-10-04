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

typedef long long ll;
constexpr int mod = 1e9 + 7;
constexpr int M = 10000;
int fact[M + 1];
int inv_fact[M + 1];

inline ll multiply(ll x, ll y) { return x * y % mod; }

inline ll binexp(ll x, int pow) {
    if (pow == 0) {
        return 1;
    }
    ll half = binexp(x, pow >> 1);
    if (pow & 1) {
        return multiply(x, multiply(half, half));
    }
    return multiply(half, half);
}

inline ll comb(int m, int n) {
    return multiply(fact[m], multiply(inv_fact[n], inv_fact[m - n]));
}

class Solution {

    long long n_choose_k(long long n, long long k) {
        if (k == 0)
            return 1;
        return (n * n_choose_k(n - 1, k - 1)) / k;
    }

  public:
    int waysToReachStair(int k) {
        int jump = 0;
        int i = 1;
        int rv = 0;
        for (auto j = 0; true; ++j) {
            if (k >= i - (j + 1)) {
                if (i >= k) {
                    // i is max height via op 1
                    // j + 1 is max op via op 2

                    int op1_avail = j + 1;
                    int op1_needed = i - k;

                    if (op1_needed == 0)
                        ++rv;
                    else
                        rv += n_choose_k(op1_avail, op1_needed);
                }
            } else
                break;
            i += 1 << j;
        }
        return rv;
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.waysToReachStair(10);
    cout << r << endl;

    r = sol.waysToReachStair(2);
    cout << r << endl;

    r = sol.waysToReachStair(1);
    cout << r << endl;

    r = sol.waysToReachStair(0);
    cout << r << endl;
}
