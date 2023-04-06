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
    bool val;
    bool isLeaf;
    Node *topLeft;
    Node *topRight;
    Node *bottomLeft;
    Node *bottomRight;

    Node()
    {
        val = false;
        isLeaf = false;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }

    Node(bool _val, bool _isLeaf)
    {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }

    Node(bool _val, bool _isLeaf, Node *_topLeft, Node *_topRight, Node *_bottomLeft, Node *_bottomRight)
    {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};

class Solution
{
public:
    Node *intersect(Node *q1, Node *q2)
    {
        if (q1->isLeaf || q2->isLeaf)
        {
            if (q1->isLeaf)
                return q1->val ? q1 : q2;
            return q2->val ? q2 : q1;
        }

        q1->topLeft = intersect(q1->topLeft, q2->topLeft);
        q1->topRight= intersect(q1->topRight, q2->topRight);
        q1->bottomLeft = intersect(q1->bottomLeft, q2->bottomLeft);
        q1->bottomRight = intersect(q1->bottomRight, q2->bottomRight);

        if (q1->topLeft->isLeaf && q1->topLeft->val &&
            q1->topRight->isLeaf && q1->topRight->val &&
            q1->bottomLeft->isLeaf && q1->bottomLeft->val &&
            q1->bottomRight->isLeaf && q1->bottomRight->val)
            q1->isLeaf = true, q1->val = 1, q1->topLeft = q1->topRight = q1->bottomLeft = q1->bottomRight = 0;

        return q1;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}