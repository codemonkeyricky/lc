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
    int maxSubarraySumCircular(vector<int>& nums) {
        const int n = nums.size();
        vi r(n);
        r[n - 1] = nums[n - 1];
        int suffix = nums[n - 1];

        /* highest sum so far - from n-1 to i */
        for (int i = n - 2; i >= 0; --i) {
            suffix += nums[i];
            r[i] = max(r[i + 1], suffix);
        }

        int maxSum = nums[0];
        int specialSum = nums[0];
        int curMax = 0;
        int prefix = 0;
        for (int i = 0; i < n; ++i) {

            /* kadane */
            curMax = max(curMax, 0) + nums[i];
            maxSum = max(maxSum, curMax);

            /* highest sum so far - from 0 to i */
            prefix += nums[i];
            if (i + 1 < n) {
                /* this accounts for the "wrap-around" case */
                specialSum = max(specialSum, prefix + r[i + 1]);
            }
        }

        return max(maxSum, specialSum);
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.maxSubarraySumCircular(vi() = {5, -4, 5});
    cout << r << endl;
}
