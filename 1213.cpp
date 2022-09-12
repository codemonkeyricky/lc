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

struct Node {
    Node *right, *down;
    int val;
    Node(Node *right, Node *down, int val): right(right), down(down), val(val) {}
};

class Skiplist
{
    Node *head;

public:
    Skiplist() { head = new Node(NULL, NULL, 0); }

    bool search(int num)
    {
        Node *p = head;
        while (p)
        {
            while (p->right and p->right->val < num)
                p = p->right;
            if (!p->right or p->right->val > num)
                p = p->down;
            else
                return true;
        }
        return false;
    }

    void add(int num)
    {
        insertPoints.clear();
        Node *p = head;
        while (p)
        {
            while (p->right and p->right->val < num)
                p = p->right;
            insertPoints.push_back(p);
            p = p->down;
        }

        Node *downNode = NULL;
        bool insertUp = true;
        while (insertUp and insertPoints.size())
        {
            Node *ins = insertPoints.back();
            insertPoints.pop_back();

            ins->right = new Node(ins->right, downNode, num);
            downNode = ins->right;

            insertUp = (rand() & 1) == 0;
        }

        if (insertUp)
            head = new Node(new Node(NULL, downNode, num), head, 0);
    }
    vector<Node *> insertPoints;

    bool erase(int num)
    {
        Node *p = head;
        bool seen = false;
        while (p)
        {
            while (p->right and p->right->val < num)
                p = p->right;
            if (!p->right or p->right->val > num)
                p = p->down;
            else
            {
                seen = true;
                p->right = p->right->right;
                p = p->down;
            }
        }
        return seen;
    }
};

class Solution
{
public:
    vector<int> arraysIntersection(vector<int> &arr1, vector<int> &arr2, vector<int> &arr3)
    {
        vector<int> inter, rv;
        set_intersection(begin(arr1), end(arr1), begin(arr2), end(arr2), begin(inter));
        set_intersection(begin(arr3), end(arr3), begin(inter), end(inter), begin(rv));
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}