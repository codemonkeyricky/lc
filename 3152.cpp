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
    vector<bool> isArraySpecial(vector<int>& nums,
                                vector<vector<int>>& queries) {
        set<int> start;
        int n = nums.size();

        for (auto i = 0; i < n; ++i)
            nums[i] %= 2;

        for (auto i = 1; i < n; ++i)
            if (nums[i - 1] == nums[i])
                start.insert(i);

        vector<bool> rv;
        for (auto& q : queries) {
            if (q[0] == q[1])
                rv.push_back(true);
            else {
                auto next_start = start.upper_bound(q[0]);
                if (next_start == start.end())
                    rv.push_back(true);
                else {
                    if (*next_start <= q[1])
                        rv.push_back(false);
                    else
                        rv.push_back(true);
                }
            }
        }
        return rv;
    }
};

int main() {
    Solution sol;
    vector<bool> r;

    r = sol.isArraySpecial(vector<int>() = {3, 7, 8},
                           vector<vector<int>>() = {{0, 2}});

    r = sol.isArraySpecial(vector<int>() = {4, 3, 1, 6},
                           vector<vector<int>>() = {{0, 2}, {2, 3}});

    r = sol.isArraySpecial(vector<int>() = {3, 4, 1, 2, 6},
                           vector<vector<int>>() = {{0, 4}});
    // cout << r << endl;
}
