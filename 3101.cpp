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
    long long countAlternatingSubarrays(vector<int>& nums) {
        int n = nums.size();

        long long rv = 0;
        int curr = 0;
        for (auto i = 0; i < n; ++i) {
            if (i == 0 || nums[i - 1] == nums[i])
                curr = 1;
            else
                ++curr;
            rv += curr;
        }
        return rv;
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.countAlternatingSubarrays(vector<int>() = {1, 0, 1, 0});
    cout << r << endl;

    r = sol.countAlternatingSubarrays(vector<int>() = {0, 1, 1, 1});
    cout << r << endl;
}
