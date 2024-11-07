#include <algorithm>
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
  public:
    long long maxBalancedSubsequenceSum(vector<int>& nums) {
        int n = nums.size();

        // vector<array<int, 2>> nums2;
        for (auto i = 0; i < n; ++i) {
            // nums2.push_back({nums[i] - i, i}); ///< for sorting / index
        }

        // set<array<int, 2>> dp; ///< for sorting / sum

        for (auto i = 0; i < n; ++i) {
            // array<int, 2> target = {nums2[i], nums2[i]};
            // auto it = set.lower_bound(dp.begin(), dp.end(), target);
            // if (it == dp.end()) {
            //     set.insert(target);
            // }
        }
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.maxBalancedSubsequenceSum(vector<int>() = {-2, -1});
    cout << r << endl;

    r = sol.maxBalancedSubsequenceSum(vector<int>() = {5, -1, -3, 8});
    cout << r << endl;

    r = sol.maxBalancedSubsequenceSum(vector<int>() = {3, 3, 5, 6});
    cout << r << endl;
}