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
    int minDifference(vector<int>& nums) {

        int n = nums.size();

        vector<int> diff;
        int p = -1;
        int unknown = 0;
        for (auto i = 0; i < n; ++i) {
            if (nums[i] != -1) {
                if (i != 0 && nums[i - 1] == -1 && p != -1) {
                    diff.push_back((nums[i] + p) / 2);
                }
                p = nums[i];
            } else {
                ++unknown;
            }
        }

        sort(diff.begin(), diff.end());

        array<int, 2> pair;
        if (diff.size())
            pair = {*diff.begin(), diff.back()};

        int i = 0, j = n - 1;
        if (diff.empty()) {
            while (i < n && nums[i] == -1)
                ++i;
            while (j >= 0 && nums[j] == -1)
                --j;
        }

        int ii = i, jj = j;
        for (; i <= j; ++i) {
            if (nums[i] == -1) {
                if (i == 0) {
                    nums[i] = pair[0];
                } else {
                    if (abs(nums[i - 1] - pair[0]) <
                        abs(nums[i - 1] - pair[1])) {
                        nums[i] = pair[0];
                    } else {
                        nums[i] = pair[1];
                    }
                }
            }
        }

        int rv = 0;
        i = ii, j = jj;
        for (i = i + 1; i <= j; ++i) {
            rv = max(rv, abs(nums[i] - nums[i - 1]));
        }

        return rv;
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.minDifference(vector<int>() = {-1, -1, 13, 34});
    cout << r << endl;

    r = sol.minDifference(vector<int>() = {1, 12});
    cout << r << endl;

    r = sol.minDifference(vector<int>() = {-1, 10, -1, 8});
    cout << r << endl;

    r = sol.minDifference(vector<int>() = {1, 2, -1, 10, 8});
    cout << r << endl;
}
