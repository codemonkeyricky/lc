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

#define ll long long
class Solution {
  public:
    int mod = 1e9 + 7;
    ll sum = 0;
    ll mmin = 1e8;

    ll ankit(vector<int>& nums, ll cost1, ll cost2, ll k) {

        ll d = k - mmin;    ///< increments to make on shortest bar
        ll n = nums.size();
        ll total = k * n - sum; ///< all increments we need to make

        // case 1
        if (2 * cost1 <= cost2)
            return total * cost1;

        // case 2

        // number of increments left after making the smallest element equal to k
        ll left = total - d;
        if (left < d)
            return (d - left) * cost1 + left * cost2;

        if (total % 2 == 0)
            return (total / 2) * cost2;
        else
            return (total / 2) * cost2 + cost1;
    }

    int minCostToEqualizeArray(vector<int>& nums, int cost1, int cost2) {

        ll mmax = 0;

        for (int i = 0; i < nums.size(); i++) {

            mmax = max(mmax, 1LL * nums[i]);
            mmin = min(mmin, 1LL * nums[i]);
            sum += nums[i];
        }

        ll ans = 1e18;

        for (int i = mmax; i <= 4 * mmax; i++) {

            ll d = ankit(nums, cost1, cost2, i);
            ans = min(ans, d);
        }

        return ans % mod;
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.minCostToEqualizeArray(vector<int>() = {1, 10}, 2, 1);
    cout << r << endl;

    r = sol.minCostToEqualizeArray(vector<int>() = {1, 14, 14, 15}, 2, 1);
    cout << r << endl;

    r = sol.minCostToEqualizeArray(vector<int>() = {4, 1}, 5, 2);
    cout << r << endl;
}
