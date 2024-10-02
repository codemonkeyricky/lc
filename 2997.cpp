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
    int minOperations(vector<int>& nums, int k) {

        int r = nums[0];
        for (auto i = 1; i < nums.size(); ++i) {
            r ^= nums[i];
        }

        int rv = 0;
        for (auto i = 0; i < 32; ++i)
            if (((1 << i) & r) ^ ((1 << i) & k))
                ++rv;

        return rv;
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.minOperations(vector<int>() = {2, 1, 3, 4}, 1);
    cout << r << endl;
}
