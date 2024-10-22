#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x), left(left), right(right) {}
};

TreeNode* recurse(vector<int>& tree, int k) {
    if (k >= tree.size() || tree[k] == -1)
        return nullptr;

    return new TreeNode(tree[k], recurse(tree, k * 2 + 1),
                        recurse(tree, k * 2 + 2));
}

TreeNode* populate(vector<int>& tree) { return recurse(tree, 0); }

void pvi(vector<int>& v) {

    for (auto& vv : v)
        cout << vv << ", ";
    cout << endl;
}

using vi = vector<int>;
using vvi = vector<vector<int>>;
using vll = vector<long long>;
using vvll = vector<vector<long long>>;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
  public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {

        priority_queue<pair<int, ListNode*>> q; // value / node

        for (auto& l : lists) {
            if (l)
                q.push({-l->val, l});
        }

        ListNode *head = nullptr, *curr = nullptr;
        while (q.size()) {
            auto [drop, n] = q.top();
            q.pop();

            if (!head)
                curr = head = n;
            else {
                curr->next = n;
                curr = curr->next;
            }

            if (n->next)
                q.push({-n->next->val, n->next});
        }

        if (curr)
            curr->next = nullptr;
        return head;
    }
};

int main() {
    Solution sol;
    int r;

    cout << r << endl;
}
