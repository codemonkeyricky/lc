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
    int maxSubarrayLength(vector<int>& nums) {
        int n = nums.size();
        vector<int> mono;
        vector<int> index;
        mono.push_back(nums[0]);
        index.push_back(0);

        int increase = true;
        for (auto i = 1; i < n && increase; ++i)
            if (nums[i - 1] > nums[i])
                increase = false;
        if (increase)
            return 0;

        int rv = 0;
        for (auto i = 1; i < n; ++i) {
            if (mono.back() < nums[i]) {
                mono.push_back(nums[i]);
                index.push_back(i);
            } else {
                auto k =
                    upper_bound(begin(mono), end(mono), nums[i]) - begin(mono);
                if (k < mono.size())
                    rv = max(rv, i - index[(int)k] + 1);
            }
        }
        return rv;
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.maxSubarrayLength(
        vector<int>() = {-204, -315, 236, -148, 505, 505, 286});
    cout << r << endl;

    r = sol.maxSubarrayLength(vector<int>() = {26, 26, 35, 72, 82});
    cout << r << endl;

    r = sol.maxSubarrayLength(vector<int>() = {7, 6, 5, 4, 3, 2, 1, 6, 10, 11});
    cout << r << endl;
}
