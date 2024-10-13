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
    int rob(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n);

        if (n == 1)
            return nums[0];

        dp[0] = nums[0];
        if (n >= 2)
            dp[1] = max(nums[0], nums[1]);

        for (auto i = 2; i < n; ++i) {
            dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
        }
        return dp[n - 1];
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.rob(vector<int>() = {2, 1, 1, 2});
    cout << r << endl;

    r = sol.rob(vector<int>() = {1, 2, 3, 1});
    cout << r << endl;

    r = sol.rob(vector<int>() = {1, 2, 3, 1});
    cout << r << endl;
}
