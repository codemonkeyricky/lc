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
    int findMin(vector<int>& nums) {

        /*
         * We have points, l, m, r. We must look at r, because we can have the
         * pathological case of rotate by one:
         * {1, 2, 3, 4, 5, 0}
         *
         * Looking at l + r isn't good enough, because in the following case,
         * minimum value can land in either left or right:
         * {5, 0, 1, 2, 3, 4}
         * {3, 4, 5, 0, 1, 2}
         *
         * We must evaluate based on m and r.
         */

#if 1
        /* solution 1 - converge from right */
        int l = 0, r = nums.size() - 1;
        while (l < r) {
            int m = (l + r) / 2;
            if (nums[m] > nums[r]) {
                l = m + 1;
            } else {
                r = m;
            }
        }
        return nums[l];
#else
        /* solution 2 - converge from left */
        int l = 0, r = nums.size() - 1;
        while (l < r) {
            int m = (l + r + 1) / 2;
            if (nums[m - 1] > nums[r]) {
                l = m;
            } else {
                r = m - 1;
            }
        }
        return nums[l];
#endif
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.findMin(vector<int>() = {4, 5, 6, 7, 0, 1, 2});
    cout << r << endl;

    r = sol.findMin(vector<int>() = {3, 4, 5, 1, 2});
    cout << r << endl;
}
