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

class Solution {
  public:
    int minCostToEqualizeArray(vector<int>& nums, int cost1, int cost2) {
        int MOD = 1e9 + 7;
        int mmax = *max_element(begin(nums), end(nums));
        priority_queue<int> q;
        int n = nums.size();
        for (auto i = 0; i < n; ++i) {
            if (nums[i] != mmax)
                q.push(-nums[i]);
        }

        long long rv = 0;
        if (cost1 * 2 <= cost2) {
            while (q.size()) {
                auto v = q.top();
                v *= -1;
                q.pop();
                rv = (rv + (mmax - v) * cost1) % MOD;
            }
        } else {
            while (q.size() >= 2) {
                auto v1 = q.top();
                v1 *= -1;
                q.pop();
                auto v2 = q.top();
                q.pop();
                v2 *= -1;

                int add = min(mmax - v1, mmax - v2);

                rv = (rv + add * cost2) % MOD;
                if (v1 + add < mmax)
                    q.push(-(v1 + add));
                if (v2 + add < mmax)
                    q.push(-(v2 + add));
            }

            if (q.size()) {
                auto v = q.top();
                q.pop();
                v *= -1;
                rv = (rv + (mmax - v) * cost1) % MOD;
            }
        }
        return rv;
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.minCostToEqualizeArray(vector<int>() = {1, 14, 14, 15}, 2, 1);
    cout << r << endl;

    r = sol.minCostToEqualizeArray(vector<int>() = {4, 1}, 5, 2);
    cout << r << endl;
}
