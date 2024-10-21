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
  public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {

        vector<double> rv;
        /* insert first k elements */
        multiset<int> set(nums.begin(), nums.begin() + k);

        /* iterater point to the middle */
        auto m = next(set.begin(), k / 2);

        int n = nums.size();
        for (auto i = k; i <= n; ++i) {

            rv.push_back(((double)*m + *next(m, k % 2 - 1)) * 0.5);

            if (i < n) {

                set.insert(nums[i]);

                /*
                 *  Use < because if num[i] is same as median, it gets inserted
                 * to the end of the same set of numbers (C++ behaviour)
                 */

                if (nums[i] < *m) {
                    /* inserted number < median - median is too big */
                    --m;
                }

                /*
                 * Use <= because if num[i] is same as median, the first
                 * instance of the same numbers gets erased.
                 */

                if (nums[i - k] <= *m) {
                    /* about to remove number < median - bump median */
                    ++m;
                }

                /* erase outgoing element */
                set.erase(set.find(nums[i - k]));
            }
        }

        return rv;
    }
};

int main() {
    Solution sol;
    int r;

    sol.medianSlidingWindow(vector<int>() = {1, 3, -1, -3, 5, 3, 6, 7}, 3);
}
