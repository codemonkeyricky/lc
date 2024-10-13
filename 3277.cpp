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
    vector<int> maximumSubarrayXor(vector<int>& nums,
                                   vector<vector<int>>& queries) {
        int n = nums.size();
        vector<vector<int>> pascal;
        pascal.push_back({1});
        for (auto i = 1; i < n; ++i) {
            vector<int> row = {1};
            for (auto k = 0; k + 1 < pascal.back().size(); ++k)
                row.push_back(pascal.back()[k] + pascal.back()[k + 1]);
            row.push_back(1);
            pascal.push_back(row);
        }

        for (auto i = 0; i < n; ++i) {

            for (auto j = i; j < n; ++j) {
            }
        }

        return {};
    }
};

int main() {
    Solution sol;
    vector<int> r;

    r = sol.maximumSubarrayXor(
        vector<int>() = {2, 8, 4, 32, 16, 1},
        vector<vector<int>>() = {{0, 2}, {1, 4}, {0, 5}});
    // cout << r << endl;
}
