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
  public:
    string smallestNumber(string num, long long t) {

        vector<int> cnt(8);
        auto tt = t;
        for (auto i = 2; i < 8 && tt != 1; ++i) {
            while (tt % i == 0) {
                tt /= i;
                ++cnt[i];
            }
        }

        if (tt != 1)
            return "-1";

        vector<vector<int>> factors(10);
        for (auto i = 2; i < 10; ++i) {
            auto ii = i;
            for (auto f = 2; f <= ii && ii != 1; ++f) {
                while (ii % f == 0) {
                    factors[i].push_back(f);
                    ii /= f;
                }
            }
        }

        long long l = 0, r = num.size();
        while (l < r) {
            auto m = (l + r + 1) / 2;

            auto ccnt = cnt;
            auto nnum = num;

            /* keep the first m digits */
            for (auto i = 0; i < m; ++i) {
                auto d = num[i] - '0';
                for (auto& f : factors[d]) {
                    ccnt[f] = max((long long)ccnt[f] - 1, 0ll);
                }
            }

            long long left = num.size() - m;

            for (auto i = 0; i < 8; ++i) {
                if (i == 2) {
                    left = left - (ccnt[i] + 2) / 3;
                } else if (i == 3) {
                    left = left - (ccnt[i] + 1) / 2;
                } else if (i == 5 || i == 7) {
                    left = left - ccnt[i];
                }
            }

            /* keep less digits */
            if (left < 0)
                r = m - 1;
            else
                l = m;
        }

        int i;
        auto keep = l;
        for (i = 0; i < keep; ++i) {
            auto d = num[i] - '0';
            for (auto& f : factors[d]) {
                cnt[f] = max((long long)cnt[f] - 1, 0ll);
            }

            if (num[i] == '0')
                num[i] = 1 + '0';
        }

        /* fill in reverse */
        string extra;
        for (int i = num.size() - 1; cnt[2] || cnt[3] || cnt[5] || cnt[7];
             --i) {

            char* ref = &num[0];
            if (i - keep < 0)
                extra += '0', ref = &extra.back();
            else
                ref = &num[i];

            if (cnt[3] >= 2) {
                /* 9 */
                *ref = 9 + '0', cnt[3] -= 2;
            } else if (cnt[2] >= 3) {
                /* 8 */
                *ref = 8 + '0', cnt[2] -= 3;
            } else if (cnt[7] >= 1) {
                /* 7 */
                *ref = 7 + '0', cnt[7] -= 1;
            } else if (cnt[2] >= 1 && cnt[3] >= 1) {
                /* 6 */
                *ref = 6 + '0', cnt[2] -= 1, cnt[3] -= 1;
            } else if (cnt[5] >= 1) {
                /* 5 */
                *ref = 5 + '0', cnt[5] -= 1;
            } else if (cnt[2] >= 2) {
                /* 4 */
                *ref = 4 + '0', cnt[2] -= 2;
            } else if (cnt[3] >= 1) {
                /* 3 */
                *ref = 3 + '0', cnt[3] -= 1;
            } else if (cnt[2] >= 1) {
                /* 2 */
                *ref = 2 + '0', cnt[2] -= 1;
            }
        }

        reverse(extra.begin(), extra.end());

        return extra + num;
    }
};

int main() {
    Solution sol;
    string r;

    r = sol.smallestNumber("10", 320);
    cout << r << endl;

    r = sol.smallestNumber("12355", 50);
    cout << r << endl;

    r = sol.smallestNumber("1234", 256);
    cout << r << endl;
}
