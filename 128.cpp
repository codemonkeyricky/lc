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
    int longestConsecutive(vector<int>& nums) {

        /* set contains all unique numbers */
        unordered_set<int> set(nums.begin(), nums.end());

        unordered_map<int, int> dp;

        int rv = 0;
        for (auto& s : set) {
            auto k = s;
            int l = 0;
            /* iterate until number doesn't exist */
            while (set.count(k)) {
                if (dp[k]) {
                    /* previousuly processed - add to it */
                    l += dp[k];
                    break;
                } else {
                    /* keep going */
                    ++l;
                    dp[k] = 1;
                }
                --k;
            }
            dp[s] = l;
            rv = max(rv, dp[s]);
        }
        return rv;
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.longestConsecutive(vector<int>() = {0, 3, 7, 2, 5, 8, 4, 6, 0, 1});
    cout << r << endl;

    r = sol.longestConsecutive(vector<int>() = {100, 4, 200, 1, 3, 2});
    cout << r << endl;
}
