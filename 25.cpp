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

    array<ListNode*, 2> reverse(ListNode* head, ListNode* tail) {

        /* terminate tail */
        tail->next = nullptr;
        auto c = head;
        ListNode* p = nullptr;
        while (c) {
            auto n = c->next;
            c->next = p;
            p = c;
            c = n;
        }

        return {p, head};
    }

  public:
    ListNode* reverseKGroup(ListNode* head, int k) {

        auto c = head;
        int kk = k;
        ListNode *p, *h, *t, *n, *nh;
        nh = n = p = h = t = nullptr;

        while (c) {
            if (!h)
                h = c;

            if (--kk == 0) {
                /* remember next to use later */
                auto n = c->next;

                /* null-terminate tail then reverse */
                c->next = nullptr;
                auto [hh, tt] = reverse(h, c);

                if (!h) {
                    /* new head is the head of the first reversed list */
                    nh = hh;
                }

                if (p) {
                    /* may be used in link the next reverse group */
                    p->next = hh;
                }

                /*
                 * update p to be tail of the last reversed group
                 * may need it in the next reverse group.
                 */
                p = tt;

                /* reset k */
                kk = k;

                /* pick up where we left off */
                c = tt;
                c->next = n;

                h = nullptr;
            }
            c = c->next;
        }

        return nh ? nh : head;
    }
};

int main() {
    Solution sol;
    int r;

    cout << r << endl;
}
