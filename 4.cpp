#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <climits>
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
    TreeNode* l;
    TreeNode* r;
    TreeNode() : val(0), l(nullptr), r(nullptr) {}
    TreeNode(int x) : val(x), l(nullptr), r(nullptr) {}
    TreeNode(int x, TreeNode* l, TreeNode* r) : val(x), l(l), r(r) {}
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
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.size() > nums2.size()) {
            swap(nums1, nums2);
        }

        int m = nums1.size(), n = nums2.size();
        int l = 0, r = m;

        /* find a split point in nums1. With any split point we can calculate
         * the responding split point in the other array. In the solved case
         * both left arrays would be smaller than both right arrays. Any
         * violation suggest the split is wrong.
         */

        /* "=" in "<="" accounts for m == 0 */
        while (l <= r) {
            int i = (l + r + 1) / 2;
            int j = (m + n + 1) / 2 - i;

            /* account for boundary when i/j are 0/m/n */

            int maxla = (i == 0) ? INT_MIN : nums1[i - 1];
            int minra = (i == m) ? INT_MAX : nums1[i];
            int maxlb = (j == 0) ? INT_MIN : nums2[j - 1];
            int minrb = (j == n) ? INT_MAX : nums2[j];

            if (maxla <= minrb && maxlb <= minra) {
                if ((m + n) % 2 == 0) {
                    return (max(maxla, maxlb) + min(minra, minrb)) / 2.0;
                } else {
                    return max(maxla, maxlb);
                }
            } else if (maxla > minrb) {
                /*
                 * max left A > min right b - reduce range
                 */

                r = i - 1;
            } else {
                /* increase range */
                l = i;
            }
        }

        return 0.0;
    }
};

int main() {
    Solution sol;
    double r;

    // r = sol.findMedianSortedArrays(vector<int>() = {}, vector<int>() = {1});
    // cout << r << endl;

    r = sol.findMedianSortedArrays(vector<int>() = {1, 2, 3, 4, 6, 8, 11},
                                   vector<int>() = {5, 7, 9, 10});
    cout << r << endl;
}
