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

    TreeNode* build(vi& preorder, vi& inorder, int k, int i, int j) {

        if (i >= j)
            return nullptr;

        /*
         * preorder[k] is root, find its pos in inorder:
         * left is left subtree and right is right subtree
         */
        int m;
        for (m = i; m < j; ++m)
            if (preorder[k] == inorder[m])
                break;

        /* find left subtree size - this is required to determine k in
         * left/right subtree */
        auto lsz = m - i;
        auto rsz = j - m - 1;

        auto left = build(preorder, inorder,
                          /* preorder position */
                          k + 1,
                          /* inorder range */
                          i, i + lsz);
        auto right = build(preorder, inorder,
                           /* preorder position */
                           k + 1 + lsz,
                           /* inorder range */
                           m + 1, j);

        return new TreeNode(preorder[k], left, right);
    }

  public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int n = preorder.size();
        return build(preorder, inorder, 0, 0, n);
    }
};

int main() {
    Solution sol;

    sol.buildTree(vi() = {1, 2, 3}, vi() = {3, 2, 1});

    sol.buildTree(vi() = {3, 9, 20, 15, 7}, vi() = {9, 3, 15, 20, 7});
}
