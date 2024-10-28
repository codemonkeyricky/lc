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
    int lengthAfterTransformations(string s, int t, vector<int>& nums) {
        int M = 1e9 + 7;

        array<int, 26> cnt = {};
        for (auto& c : s) {
            ++cnt[c - 'a'];
        }

        for (auto tt = 0; tt < t; ++tt) {
            array<int, 26> next = {};
            for (auto i = 0; i < 26; ++i) {
                for (auto j = 1; j <= nums[i]; ++j) {
                    auto k = (i + j) % 26;
                    next[k] = (next[k] + cnt[i]) % M;
                }
            }
            cnt = next;
        }

        long long sum = 0;
        for (auto i = 0; i < 26; ++i)
            sum = (sum + cnt[i]) % M;
        return sum;
    }
};

int main() {
    Solution sol;
    int r;

    // r = sol.lengthAfterTransformations(
    //     "azbk", 3, vector<int>() = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    //                                 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2});
    // cout << r << endl;

    // r = sol.lengthAfterTransformations(
    //     "azbk", 2, vector<int>() = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    //                                 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2});
    // cout << r << endl;

    // r = sol.lengthAfterTransformations(
    //     "azbk", 1, vector<int>() = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    //                                 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2});
    // cout << r << endl;

    r = sol.lengthAfterTransformations(
        "abcyy", 52, vector<int>() = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2});
    cout << r << endl;

    r = sol.lengthAfterTransformations(
        "abcyy", 26, vector<int>() = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2});
    cout << r << endl;

    r = sol.lengthAfterTransformations(
        "abcyy", 2, vector<int>() = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                     1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2});
    cout << r << endl;
}
