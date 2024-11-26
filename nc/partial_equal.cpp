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
    bool canPartition(vector<int>& nums) {

        auto sum = accumulate(nums.begin(), nums.end(), 0ll);

        /* can we split the set into two halves? */
        if (sum % 2)
            return false;

        unordered_set<int> set, replace;
        for (auto& n : nums) {
            auto replace = set;
            replace.insert(n);
            for (auto& s : set)
                replace.insert(s + n);
            swap(set, replace);
        }

        return set.count(sum / 2);
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.canPartition(vector<int>() = {1, 2, 3, 4});
    cout << r << endl;
}
