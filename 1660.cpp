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
    void dfs(TreeNode *root, int invalid)
    {
        if (root)
        {
            if (root->left && root->left->val == invalid)
                root->left = nullptr;
            if (root->right && root->right->val == invalid)
                root->right = nullptr;

            dfs(root->left, invalid);
            dfs(root->right, invalid);
        }
    }

public:
    TreeNode *correctBinaryTree(TreeNode *root)
    {
        vector<TreeNode *> q;
        q.push_back(root);
        int invalid = -1;
        while (q.size())
        {
            vector<TreeNode *> nq;
            for (auto i = 0; i < q.size(); ++i)
            {
                auto n = q[i];
                if (n->left)
                    nq.push_back(n->left);
                if (n->right)
                    nq.push_back(n->right);
            }

            unordered_set<int> seen;
            for (int i = nq.size() - 1; i >= 0; --i)
                if (nq[i]->right && seen.count(nq[i]->right->val))
                    invalid = nq[i]->val;
                else
                    seen.insert(nq[i]->val);

            if (invalid != -1)
                break;

            swap(q, nq);
        }

        dfs(root, invalid);

        return root;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}