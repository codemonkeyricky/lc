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

    void quick() {}

  public:
    vector<int> sortArray(vector<int>& nums) {
        merge(nums, 0, nums.size());

        return nums;
    }
};

int main() {
    Solution sol;
    vector<int> r;

    r = sol.sortArray(vector<int>() = {5, 2, 3, 1});
    pvi(r);
}
