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

    int dfs(string& nums, int even, int odd, int sum) {

        /* add even,  subtract odd */

        int k = nums.size() - even - odd;

        /* base case */
        if (even == 0 || odd == 0) {
            auto r =
                accumulate(nums.begin() + k, nums.end(), 0ll,
                           [](long long a, char b) { return a + b - '0'; });
            if (even)
                return (sum + r) == 0;
            else
                return (sum - r) == 0;
        }

        /* general case */

        long long a = dfs(nums, even - 1, odd, sum + nums[k] - '0');
        long long b = dfs(nums, even, odd - 1, sum - nums[k] - '0');

        return a + b;
    }

  public:
    int countBalancedPermutations(string num) {
        int n = num.size();
        return dfs(num, (n + 1) / 2, n / 2, 0);
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.countBalancedPermutations("123");
    cout << r << endl;
}
