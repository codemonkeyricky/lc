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

class Node
{
public:
    int val;
    vector<Node *> children;

    Node() {}

    Node(int _val)
    {
        val = _val;
    }

    Node(int _val, vector<Node *> _children)
    {
        val = _val;
        children = _children;
    }
};

class Solution
{
    Node *detach(Node *root, Node *p, Node *q)
    {
        Node *n = nullptr;
        if (root->val != p->val)
        {
            vector<Node *> new_children;
            for (auto &curr : root->children)
            {
                if (q && root->val == q->val && curr->val == p->val)
                    return root;

                if (n = detach(curr, p, q))
                    new_children.push_back(n);
            }
            swap(root->children, new_children);
            n = root;
        }
        return n;
    }

    void attach(Node *root, Node *p, Node *q)
    {
        for (auto &curr : root->children)
            if (root->val == q->val && curr->val == p->val)
                return;

        if (root->val == q->val)
        {
            root->children.push_back(p);
            return;
        }

        for (auto &curr : root->children)
            attach(curr, p, q);
    }

    bool isCase1(Node *root, Node *p, Node *q, unordered_set<int> &ancester)
    {
        ancester.insert(root->val);

        for (auto &curr : root->children)
            if ((ancester.count(p->val) && curr->val == q->val) || isCase1(curr, p, q, ancester))
                return true;

        ancester.erase(root->val);

        return false;
    }

public:
    Node *moveSubTree(Node *root, Node *p, Node *q)
    {
        unordered_set<int> ancester;
        if (isCase1(root, p, q, ancester))
        {
            // p contains q
            // detach q from p. 
            detach(p, q, nullptr);

            swap(p->val, q->val);
            swap(p->children, q->children);
            p->children.push_back(q);

            return root;
        }
        else
        {
            detach(root, p, q);
            attach(root, p, q);
        }
        return root;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}