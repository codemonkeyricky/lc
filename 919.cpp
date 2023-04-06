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
class CBTInserter
{
    queue<TreeNode *> curr, next;
    TreeNode *_root; 

public:
    CBTInserter(TreeNode *root)
    {
        _root = root;
        curr.push(root);
        bool keep_going = true;
        do
        {
            while (curr.size())
            {
                auto n = curr.front();
                if (n->left)
                    next.push(n->left);
                if (n->right)
                    next.push(n->right);

                if (!n->right)
                {
                    keep_going = false;
                    break;
                }
                curr.pop();
            }

            if (keep_going)
                swap(next, curr);

        } while (keep_going);
    }

    int insert(int val)
    {
        while (curr.size())
        {
            if (!curr.front()->left)
            {
                curr.front()->left = new TreeNode(val);
                next.push(curr.front()->left);
                return curr.front()->val;
            }
            else if (!curr.front()->right)
            {
                curr.front()->right = new TreeNode(val);
                next.push(curr.front()->right);
                return curr.front()->val;
            }
            else 
                curr.pop();

            if (curr.empty())
                swap(curr, next);
        }

        return -1;
    }

    TreeNode *get_root()
    {
        return _root;
    }
};

/**
 * Your CBTInserter object will be instantiated and called as such:
 * CBTInserter* obj = new CBTInserter(root);
 * int param_1 = obj->insert(val);
 * TreeNode* param_2 = obj->get_root();
 */

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}