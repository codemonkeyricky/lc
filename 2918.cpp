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

class Solution {
  public:
    long long minSum(vector<int>& nums1, vector<int>& nums2) {
        auto sum1 = accumulate(begin(nums1), end(nums1), 0ll);
        auto sum2 = accumulate(begin(nums2), end(nums2), 0ll);

        auto zero1 = count(begin(nums1), end(nums1), 0ll);
        auto zero2 = count(begin(nums2), end(nums2), 0ll);

        /* can't catch up */
        if ((sum2 + zero2 > sum1 + zero1) && zero1 == 0)
            return -1;

        /* can't catch up */
        if ((sum2 + zero2 < sum1 + zero1) && zero2 == 0)
            return -1;

        return max(sum2 + zero2, sum1 + zero1);
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.minSum(vector<int>() = {3, 2, 0, 1, 0}, vector<int>() = {6, 5, 0});
    cout << r << endl;
}
