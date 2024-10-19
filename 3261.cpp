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

void pvll(vector<long long>& v) {

    for (auto& vv : v)
        cout << vv << ", ";
    cout << endl;
}

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
    vector<long long> countKConstraintSubstrings(string s, int k,
                                                 vector<vector<int>>& queries) {
        long long n = s.size(), l, r, one = 0, zero = 0, cur, i, len;

        /* a[] contains total number of valid substrings at index */
        vector<long long> ans, pre(n + 1), a(n);
        l = 0;
        for (r = 0; r < n; r++) {
            s[r] == '1' ? one++ : zero++;
            while (zero > k && one > k) {
                s[l] == '1' ? one-- : zero--;
                l++;
            }
            cur = r - l + 1;
            a[r] = cur;
        }

        /* prefix sum */
        for (i = 0; i < n; i++) {
            pre[i + 1] = pre[i] + a[i];
        }

        for (auto& q : queries) {
            l = q[0];
            r = q[1];
            cur = 0;
            len = 0;
            for (i = l; i <= r; i++) {
                len++;
                if (a[i] <= len) {
                    cur = cur + pre[r + 1] - pre[i];
                    break;
                } else {
                    cur = cur + len;
                }
            }
            ans.push_back(cur);
        }
        return ans;
    }
};

int main() {
    Solution sol;
    vll r;

    r = sol.countKConstraintSubstrings("0001111", 2, vvi() = {{0, 6}});
    pvll(r);
}
