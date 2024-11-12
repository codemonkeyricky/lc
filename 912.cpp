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

void pvi(vector<int>& v) {

    for (auto& vv : v)
        cout << vv << ", ";
    cout << endl;
}

using vi = vector<int>;
using vvi = vector<vector<int>>;
using vll = vector<long long>;
using vvll = vector<vector<long long>>;

class Solution {

    /* OC - TLE */

    void merge(vector<int>& nums, int i, int j) {

        /* base condition */

        if (j - i <= 1)
            return;

        int m = (i + j) / 2;
        merge(nums, i, m);
        merge(nums, m, j);

        /* need to duplicate before copy */

        auto left = vector<int>(nums.begin() + i, nums.begin() + m);
        auto right = vector<int>(nums.begin() + m, nums.begin() + j);

        /* core sort algorithm */

        int l = 0, r = 0, w = i;
        while (l < left.size() || r < right.size()) {
            if (l < left.size() && r < right.size()) {
                if (left[l] <= right[r])
                    nums[w++] = left[l++];
                else
                    nums[w++] = right[r++];
            } else if (l < left.size()) {
                nums[w++] = left[l++];
            } else {
                nums[w++] = right[r++];
            }
        }
    }

    int partition(vector<int>& nums, int low, int high) {

        if (low >= high)
            return -1;

        /*
         * [0] is the pivot
         * everything smaller than pivot is on the left, everything bigger is on
         * the right.
         */
        int pivot = low, l = pivot + 1, r = high;
        while (l <= r) {
            if (nums[l] < nums[pivot]) {
                /* already smaller */
                ++l;
            } else if (nums[r] >= nums[pivot]) {
                /* already bigger */
                --r;
            } else {
                /* l and r both violate - swap them */
                swap(nums[l], nums[r]);
            }
        }
        /* moves pivot to place */
        swap(nums[pivot], nums[r]);

        return r;
    }

    /* TLE in OJ */

    void quick(vector<int>& nums, int low, int high) {

        if (low >= high)
            return;

        /*
         * quick sort ensures pivot is always in the final spot, and all smaller
         * elementse are left and bigger elements are right. Recursively sort
         * left and right.
         */

        int pivot = partition(nums, low, high);
        quick(nums, low, pivot);
        quick(nums, pivot + 1, high);
    }

  public:
    vector<int> sortArray(vector<int>& nums) {
        // merge(nums, 0, nums.size());

        quick(nums, 0, nums.size() - 1);

        return nums;
    }
};

int main() {
    Solution sol;
    vector<int> r;

    r = sol.sortArray(vector<int>() = {5, 2, 3, 1});
    pvi(r);
}
