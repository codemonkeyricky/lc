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

    long long uniq_subarray(vector<int>& nums, int k) {

        int n = nums.size();

        vector<int> map(1e5 + 1);
        int uniq = 0;

        long long rv = 0;
        for (long long i = 0, j = 0; j < n; ++j) {
            if (map[nums[j]]++ == 0)
                ++uniq;

            while (uniq > k) {
                if (--map[nums[i]] == 0)
                    --uniq;
                ++i;
            }
            rv += (j - i + 1);
        }

        return rv;
    }

  public:
    int medianOfUniquenessArray(vector<int>& nums) {
        int n = nums.size();
        int l = 1, r = n;

        long long total = (long long)n * (n + 1) / 2;
        while (l < r) {
            int m = (l + r) / 2;
            long long cnt = uniq_subarray(nums, m);
            if (cnt * 2 >= total)
                r = m;
            else
                l = m + 1;
        }

        return l;
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.medianOfUniquenessArray(
        vector<int>() = {91, 64, 76, 18, 61, 55, 46, 93, 65, 99});
    cout << r << endl;

    r = sol.medianOfUniquenessArray(vector<int>() = {3, 4, 3, 4, 5});
    cout << r << endl;

    r = sol.medianOfUniquenessArray(vector<int>() = {1, 2, 3});
    cout << r << endl;
}
