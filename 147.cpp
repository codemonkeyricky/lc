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

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution
{
    ListNode *insert(ListNode *root, ListNode *node)
    {
        auto rv = node;
        if (root)
        {
            if (node->val < root->val)
                node->next = root;
            else
            {
                rv = root;
                while (root && root->next && root->next->val < node->val)
                    root = root->next;
                auto next = root->next;
                root->next = node;
                node->next = next;
            }
        }
        return rv; 
    }

public:
    ListNode *insertionSortList(ListNode *head)
    {
        ListNode *rv = nullptr;
        while (head)
        {
            auto next = head->next;
            head->next = nullptr;
            rv = insert(rv, head);
            head = next; 
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