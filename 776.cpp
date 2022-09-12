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
public:
    vector<TreeNode *> splitBST(TreeNode *curr, int V)
    {
        vector<TreeNode *> rv(2, nullptr);
        if (curr)
        {
            if (curr->val > V)
            {
                rv[1] = curr;
                auto r = splitBST(curr->left, V);
                curr->left = r[1];
                rv[0] = r[0];
            }
            else
            {
                rv[0] = curr;
                auto r = splitBST(curr->right, V);
                curr->right = r[0];
                rv[1] = r[1];
            }
        }

        return rv;
    } 
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}