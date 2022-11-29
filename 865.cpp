#include <iostream>
#include <vector>
#include <cassert>
#include <stack>
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <bitset>
#include <numeric>
#include <cmath>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

TreeNode *recurse(vector<int> &tree, int k)
{
    if (k >= tree.size() || tree[k] == -1)
        return nullptr;

    return new TreeNode(tree[k], recurse(tree, k * 2 + 1), recurse(tree, k * 2 + 2));
}

TreeNode *populate(vector<int> &tree)
{
    return recurse(tree, 0);
}

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution
{
    int depth(TreeNode *root)
    {
        if (root)
            return 1 + max(depth(root->left), depth(root->right));
        return 0;
    }

    int dfs(TreeNode *root, int d, int t, TreeNode **rv)
    {
        if (root)
        {
            auto l = dfs(root->left, d + 1, t, rv);
            auto r = dfs(root->right, d + 1, t, rv);
            if (l == r && l == t)
                *rv = root;
            return 1 + max(l, r);
        }
        return d;
    }

public:
    TreeNode *subtreeWithAllDeepest(TreeNode *root)
    {
        auto d = depth(root);
        TreeNode *rv = nullptr;
        dfs(root, 0, d, &rv);
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}