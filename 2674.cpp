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
public:
    vector<ListNode *> splitCircularLinkedList(ListNode *list)
    {
        if(list->next->next == list)
        {
            auto first = list, second = list->next;
            first->next = first, second->next = second;
            return {first, second};
        }

        auto first = list; 
        auto slow = first, fast = first;
        while (fast->next != first && fast->next->next != first)
            fast = fast->next->next, slow = slow->next;

        auto second = slow->next;
        slow->next = first;
        if (fast->next == first)
            fast->next = second; 
        else 
            fast->next->next = second; 

        return {first, second}; 
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}