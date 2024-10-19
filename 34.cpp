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
    vector<int> searchRange(vector<int>& nums, int target) {
        int l = 0, r = nums.size() - 1;

        vector<int> rv = {-1, -1};

        /* find the right boundary */
        while (l < r) {
            int m = (l + r + 1) / 2;
            if (nums[m] <= target) {
                /* keep pushing right */
                l = m;
            } else {
                r = m - 1;
            }
        }

        if (nums[l] != target)
            return rv;

        rv[1] = l;

        l = 0, r = nums.size() - 1;
        while (l < r) {
            int m = (l + r) / 2;
            if (target <= nums[m]) {
                /* keep pushing left */
                r = m;
            } else {
                l = m + 1;
            }
        }

        rv[0] = r;

        return rv;
    }
};

int main() {
    Solution sol;
    vector<int> r;

    r = sol.searchRange(vector<int>() = {5, 7, 7, 8, 8, 10}, 8);
    // cout << r << endl;
}
