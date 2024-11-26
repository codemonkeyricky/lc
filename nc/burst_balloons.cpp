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
    int dfs(vector<int>& nums, int i, int j) {

        if (i == j)
            return nums[i - 1] * nums[i] * nums[i + 1];

        int rv = 0;
        for (auto k = i; k <= j; ++k) {
            int c = nums[k] * nums[i - 1] * nums[j + 1];
            int l = dfs(nums, i, k - 1);
            int r = dfs(nums, k + 1, j);
            rv = max(rv, l + c + r);
        }
        return rv;
    }

  public:
    int maxCoins(vector<int>& nums) {
        nums.insert(nums.begin(), 1);
        nums.push_back(1);
        return dfs(nums, 1, nums.size() - 2);
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.maxCoins(vector<int>() = {3, 1, 5, 8});
    cout << r << endl;

    r = sol.maxCoins(vector<int>() = {4, 2, 3, 7});
    cout << r << endl;
}
