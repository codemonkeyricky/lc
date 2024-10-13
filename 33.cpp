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
    int search(vector<int>& nums, int target) {
        int n = nums.size();

        int l = 0, r = n;
        while (l < r) {
            int m = (l + r) / 2;

            int num = (nums[0] > nums[m]) == (target < nums[0])
                          ? nums[m]
                          : (target < nums[0] ? -1e9 : 1e9);

            if (num < target)
                l = m + 1;
            else
                r = m;
        }
        if (l >= n)
            return -1;

        return nums[l] == target ? l : -1;
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.search(vector<int>() = {3, 4, 5, 6, 1, 2}, 2);
    cout << r << endl;

    r = sol.search(vector<int>() = {3, 1}, 3);
    cout << r << endl;

    r = sol.search(vector<int>() = {1, 3}, 3);
    cout << r << endl;

    r = sol.search(vector<int>() = {1}, 0);
    cout << r << endl;

    r = sol.search(vector<int>() = {3, 4, 5, 6, 7, 0, 1, 2}, 0);
    cout << r << endl;

    r = sol.search(vector<int>() = {4, 5, 6, 7, 0, 1, 2}, 5);
    cout << r << endl;
}
