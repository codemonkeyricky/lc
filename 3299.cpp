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
    int getSum(vector<int>& nums) {

        unordered_map<int, int> cnt, sum;

        int rv = 0;
        for (auto& n : nums) {
            cnt[n] += cnt[n - 1] + 1;
            sum[n] += sum[n - 1] + n * (cnt[n - 1] + 1);
            rv += sum[n];
        }

        // unordered_map<int, int> dec_len, dec_sum;
        // for (auto& n : nums) {
        //     dec_len[n] += dec_len[n + 1] + 1;
        //     dec_sum[n] += n * dec_len[n] + dec_sum[n + 1];// - (n + 1);
        //     rv += dec_sum[n];
        // }

        return rv;
    }
};

int main() {
    Solution sol;
    int r;

    // r = sol.getSum(vector<int>() = {1, 4, 2, 3});
    // cout << r << endl;

    r = sol.getSum(vector<int>() = {1, 2, 2});
    cout << r << endl;
}