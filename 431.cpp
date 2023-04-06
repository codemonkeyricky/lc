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
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};

class Codec
{
public:
    // Encodes an n-ary tree to a binary tree.
    TreeNode *encode(Node *root)
    {
        // left child: child chain, right child: lower siblings
        if (root == nullptr)
            return nullptr;

        TreeNode *rv = new TreeNode(root->val);
        if (root->children.size() == 0)
            return rv;

        rv->left = encode(root->children[0]);
        TreeNode *now = rv->left;
        for (int i = 1; i < root->children.size(); ++i, now = now->right)
            now->right = encode(root->children[i]);

        return rv;
    }

    // Decodes your binary tree to an n-ary tree.
    Node *decode(TreeNode *root)
    {
        if (root == nullptr)
            return nullptr;

        Node *rv = new Node;
        rv->val = root->val;
        TreeNode *now = root->left;
        while (now)
        {
            rv->children.push_back(decode(now));
            now = now->right;
        }
        return rv;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.decode(codec.encode(root));

int main()
{
}