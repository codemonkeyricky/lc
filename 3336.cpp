#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
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
using vvvi = vector<vector<vector<int>>>;
using vll = vector<long long>;
using vvll = vector<vector<long long>>;

class Solution {
    const int mod = 1e9 + 7;
    vvvi dp; 

  public:
    int dfs(int k, vector<int>& nums, int g1, int g2) {
        // g1 == gcd of g1 subsequence till now
        // g2 = gcd of g2 subsequence till now

        if (k == nums.size()) {
            return (g1 && g2) && (g1 == g2);
        }

        if (dp[k][g1][g2] == 0) {

            /* skip */
            int skip = dfs(k + 1, nums, g1, g2);

            /* propagate to g1 */
            int take1 = dfs(k + 1, nums, __gcd(g1, nums[k]), g2);

            /* propagate to g2 */
            int take2 = dfs(k + 1, nums, g1, __gcd(g2, nums[k]));

            // Summing up all the possibilites
            dp[k][g1][g2] = (0ll + skip + take1 + take2) % mod + 1;
        }
        return dp[k][g1][g2] - 1;
    }

    int subsequencePairCount(vector<int>& nums) {
        dp = vvvi(201, vvi(201, vi(201)));
        return dfs(0, nums, 0, 0);
    }
};

int main() {
    Solution sol;
    int r;

    cout << r << endl;
}
