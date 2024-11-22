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
    int longestNiceSubarray(vector<int>& nums) {
#if 0
        int n = nums.size();
        int v = 0;
        int rv = 0;
        for (auto i = 0, j = 0; j < n; ++j) {
            /* each bit can appear at most once */
            while (v & nums[j])
                v ^= nums[i++];
            /* record bits seen */
            v ^= nums[j];
            rv = max(rv, j - i + 1);
        }
        return rv;
#else
        array<int, 32> ones = {};
        int rv = 0;
        int n = nums.size();
        for (auto i = 0, j = 0; j < n; ++j) {

            int valid = true;
            for (auto b = 0; b < 32; ++b) {
                if (nums[j] & (1 << b)) {
                    ++ones[b];
                }
                if (ones[b] > 1)
                    valid = false;
            }

            while (!valid) {
                valid = true;
                for (auto b = 0; b < 32; ++b) {
                    if (nums[i] & (1 << b)) {
                        if (--ones[b] > 1)
                            valid = false;
                    }
                }
                ++i;
            }

            rv = max(rv, j - i + 1);
        }
        return rv;
#endif
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.longestNiceSubarray(vector<int>() = {2, 1, 1, 4});
    cout << r << endl;

    r = sol.longestNiceSubarray(
        vector<int>() = {84139415,  693324769, 614626365, 497710833, 615598711,
                         264,       65552,     50331652,  1,         1048576,
                         16384,     544,       270532608, 151813349, 221976871,
                         678178917, 845710321, 751376227, 331656525, 739558112,
                         267703680});
    cout << r << endl;

    r = sol.longestNiceSubarray(vector<int>() = {3, 8, 48});
    cout << r << endl;

    r = sol.longestNiceSubarray(vector<int>() = {3, 1, 5, 11, 13});
    cout << r << endl;
}