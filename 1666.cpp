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

// Definition for a Node.
class Node
{
public:
    int val;
    Node *left;
    Node *right;
    Node *parent;
};

class Solution
{
public:
    Node *flipBinaryTree(Node *root, Node *leaf)
    {
        if (root == leaf)
            return leaf;

        if (leaf->left)
            leaf->right = leaf->left;

        if (leaf == leaf->parent->left)
            leaf->parent->left = NULL;
        else
            leaf->parent->right = NULL;

        leaf->left = flipBinaryTree(root, leaf->parent);
        leaf->left->parent = leaf;
        leaf->parent = NULL;
        return leaf;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}