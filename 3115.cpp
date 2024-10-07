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
    int maximumPrimeDifference(vector<int>& nums) {

        vector<int> is_prime(101, true);
        is_prime[0] = is_prime[1] = false;
        for (auto i = 2; i < 101; ++i) {
            if (is_prime[i]) {
                int k = i;
                while (k + i < 101) {
                    is_prime[k + i] = false;
                    k += i;
                }
            }
        }

        int rv = 0, p = 1e9;
        for (auto i = 0; i < nums.size(); ++i) {
            if (is_prime[nums[i]]) {
                p = min(p, i);
                rv = max(rv, i - p);
            }
        }

        return rv;
    }
};

int main() {
    Solution sol;
    int r;

    cout << r << endl;
}
