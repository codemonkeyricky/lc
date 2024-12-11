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
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        set<vector<int>> rv;

        int n = nums.size();
        for (auto i = 0; i < (1 << n); ++i) {
            vector<int> r;
            int ii = i;
            while (ii) {
                auto b = ii & -ii;
                auto k = log2(b);
                r.push_back(nums[k]);
                ii -= b;
            }

            sort(r.begin(), r.end());
            rv.insert(r);
        }
        return vector<vector<int>>(rv.begin(), rv.end());
    }
};

int main() {
    Solution sol;
    int r;

    sol.subsetsWithDup(vector<int>() = {1, 2, 1});
}