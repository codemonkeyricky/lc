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

    int almost_equal(int x, int y) {
        vector<array<int, 2>> diff;
        int k = 0;
        while (x || y) {
            int xx = x % 10;
            int yy = y % 10;

            if (xx != yy)
                diff.push_back({xx, yy});

            x /= 10, y /= 10;
        }

        if (diff.size() == 2)
            return (diff[0][1] == diff[1][0]) && (diff[0][0] == diff[1][1]);

        return diff.size() == 0;
    }

  public:
    int countPairs(vector<int>& nums) {
        int n = nums.size(), rv = 0;
        for (auto i = 0; i < n; ++i)
            for (auto j = 0; j < i; ++j)
                rv += almost_equal(nums[i], nums[j]);
        return rv;
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.countPairs(vector<int>() = {1, 1, 1, 1, 1});
    cout << r << endl;

    r = sol.countPairs(vector<int>() = {3, 12, 30, 17, 21});
    cout << r << endl;
}
