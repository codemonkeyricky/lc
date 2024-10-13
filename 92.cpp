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

    ListNode* reverse(ListNode* h, ListNode* t) {

        ListNode *p = h, *c = h->next, *n = nullptr;
        h->next = nullptr;
        /* 
         * p + c are the current "set". cache c->next before setting it to p 
         * stop when p == t
         */
        while (p != t) {
            n = c->next;
            c->next = p;
            p = c;
            c = n;
        }
        return t;
    }

  public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {

        ListNode *h, *t, *p = nullptr, *ph = nullptr, *nt = nullptr;
        auto c = head;
        int k = 1;

        /* find the left and right node and the nodes before and after */
        while (c) {
            if (k == left)
                h = c, ph = p;
            if (k == right)
                t = c, nt = c->next;
            p = c;
            c = c->next;
            ++k;
        }

        auto hh = reverse(h, t);

        /* "stich" the reversed linked list back */
        if (ph)
            ph->next = hh;
        h->next = nt;

        /* special handling when left == 1 */
        return ph ? head : hh;
    }
};

int main() {
    Solution sol;
    int r;

    cout << r << endl;
}
