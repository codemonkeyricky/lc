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
    int divisibleTripletCount(vector<int>& nums, int d) {
        unordered_map<int, int> cnt;
        for (auto& n : nums) {
            if (n % d != 0)
                n %= d;
            else
                n = d;
            ++cnt[n];
        }

        int n = nums.size(), rv = 0;
        for (auto j = 0; j < n; ++j) {
            --cnt[nums[j]];
            for (auto i = 0; i < j; ++i) {
                rv += cnt[d - nums[i] - nums[j]];
                rv += cnt[d * 2 - nums[i] - nums[j]];
                rv += cnt[d * 3 - nums[i] - nums[j]];
            }
        }
        return rv;
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.divisibleTripletCount(vector<int>() = {76, 65, 57}, 3);
    cout << r << endl;

    r = sol.divisibleTripletCount(vector<int>() = {3, 3, 3, 3}, 6);
    cout << r << endl;

    r = sol.divisibleTripletCount(vector<int>() = {3, 3, 3, 3}, 3);
    cout << r << endl;

    r = sol.divisibleTripletCount(vector<int>() = {3, 3, 4, 7, 8}, 5);
    cout << r << endl;
}
