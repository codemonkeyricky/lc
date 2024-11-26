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
    int partition(vector<int>& nums, int i, int j) {
        int p = i++;
        while (i <= j) {
            if (nums[i] < nums[p]) {
                ++i;
            } else if (nums[j] >= nums[p]) {
                --j;
            } else {
                swap(nums[i], nums[j]);
            }
        }
        /* move pivot to where it should be */
        swap(nums[j], nums[p]);
        return j;
    }

  public:
    int findKthLargest(vector<int>& nums, int k) {
        int p = -1;
        int n = nums.size();
        int l = 0, r = n - 1;
        k = n - k;
        while (l < r) {
            p = partition(nums, l, r);
            if (k == p) {
                return nums[k];
            } else if (k < p) {
                /* sort left */
                r = p - 1;
            } else { // k > p
                /* sort right */
                l = p + 1;
            }
        }
        return nums[l];
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.findKthLargest(vector<int>() = {2, 3, 1, 5, 4}, 2);
    cout << r << endl;

    r = sol.findKthLargest(vector<int>() = {2, 3, 1, 1, 5, 5, 4}, 3);
    cout << r << endl;
}
