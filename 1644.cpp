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
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution
{
    TreeNode *dfs(TreeNode *curr, TreeNode *p, TreeNode *q, TreeNode **rv)
    {
        if (curr)
        {
            auto l = dfs(curr->left, p, q, rv);
            auto r = dfs(curr->right, p, q, rv);

            if (l == p && r == q)
                *rv = curr;
            else if (r == p && l == q)
                *rv = curr;
            else if (curr == p && (l == q || r == q))
                *rv = curr;
            else if (curr == p && (r == q || l == q))
                *rv = curr;
            else if (curr == q && (l == p || r == p))
                *rv = curr;
            else if (curr == q && (r == p || l == p))
                *rv = curr;

            if (*rv == nullptr)
            {
                if (curr == p)
                    return p;
                else if (curr == q)
                    return q;
                return l ? l : r ? r : nullptr;
            }
            return nullptr;
            
        }
        return nullptr;
    }

public:
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        TreeNode *rv = nullptr; 
        dfs(root, p, q, &rv);
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}