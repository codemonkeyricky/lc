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
    vector<ListNode *> splitListToParts(ListNode *head, int k)
    {
        int l = 0;
        ListNode *curr = head;
        while (curr)
            curr = curr->next, ++l;

        int s = 0, slen = 0;
        vector<ListNode *> rv;
        curr = head;
        auto kk = k;
        while (curr)
        {
            if (s == 0)
                rv.push_back(curr), s = 0, slen = l / k + ((l % k) ? 1 : 0);

            auto next = curr->next;
            if (++s >= slen) 
                curr->next = nullptr, s = 0, l -= slen, --k;
            curr = next;
        }

        while (rv.size() != kk)
            rv.push_back(nullptr);

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}