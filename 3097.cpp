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
    int get_mask(array<int, 32>& bits) {
        int rv = -1;
        for (auto k = 0; k < 32; ++k)
            if (bits[k] == 0)
                rv &= ~(1 << k);
        return rv;
    }

  public:
    int minimumSubarrayLength(vector<int>& nums, int k) {
        int n = nums.size();
        int rv = 1e9;

        array<int, 32> bits = {};

        for (auto i = 0, j = 0; j < n; ++j) {
            for (auto k = 0; k < 32; ++k)
                bits[k] += !!((1 << k) & nums[j]);

            while (i <= j && get_mask(bits) >= k) {
                rv = min(rv, j - i + 1);
                for (auto k = 0; k < 32; ++k)
                    bits[k] -= !!((1 << k) & nums[i]);
                ++i;
            }
        }
        return rv == 1e9 ? -1 : rv;
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.minimumSubarrayLength(vector<int>() = {1, 2}, 0);
    cout << r << endl;

    r = sol.minimumSubarrayLength(vector<int>() = {2, 1, 8}, 10);
    cout << r << endl;

    r = sol.minimumSubarrayLength(vector<int>() = {1, 2, 3}, 2);
    cout << r << endl;
}
