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
    int minChanges(vector<int>& nums, int k) {
        int n = nums.size();

        vector<int> d;
        for (auto k = 0; k < n / 2; ++k)
            d.push_back(abs(nums[k] - nums[n - k - 1]));
        sort(begin(d), end(d));

        map<int, int> cnt;
        for (auto& dd : d)
            ++cnt[dd];

        int rv = 1e9;
        for (auto x = 0; x < 10001; ++x) {
            auto it1 = lower_bound(begin(d), end(d), x - k / 2);
            auto it2 = upper_bound(begin(d), end(d), x);
            int x2 = it1 - begin(d);
            int x1 = end(d) - it1 - cnt[x];
            rv = min(rv, x1 + x2 * 2);
        }

        return rv;
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.minChanges(vector<int>() = {1,  1,  1,  1,  0,  0,  0,  5,  4,  3,
                                        19, 17, 16, 15, 15, 15, 19, 19, 19, 19},
                       20);
    cout << r << endl;

    r = sol.minChanges(vector<int>() = {0, 1, 2, 3, 3, 6, 5, 4}, 6);
    cout << r << endl;

    r = sol.minChanges(vector<int>() = {1, 0, 1, 2, 4, 3}, 4);
    cout << r << endl;
}