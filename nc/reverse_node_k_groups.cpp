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
    ListNode* reverse(ListNode* h) {
        auto c = h;
        ListNode* p = nullptr;
        while (c) {
            auto n = c->next;
            c->next = p;
            p = c;
            c = n;
        }
        return p;
    }

    ListNode* get_tail(ListNode* h) {
        ListNode* p = nullptr;
        auto c = h;
        while (c) {
            p = c;
            c = c->next;
        }
        return p;
    }

  public:
    /*
     *  case 1: number of nodes is divisible by k
     *  case 2: number of nodes is > k but not divisible by k
     *  case 3: number of nodes is < k
     */
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* head_to_return = nullptr;
        ListNode* pt = nullptr; /* prev tail */
        auto c = head;
        while (c) {
            auto kk = k;
            auto hh = c;
            while (--kk > 0 && c) {
                c = c->next;
            }

            if (kk) {
                /* account for the last bit that's not k */
                if (pt)
                    pt->next = hh;
                break;
            }

            /* remember where we need to start next iteration */
            auto n = c->next;

            /* reverse */
            c->next = nullptr;
            auto nh = reverse(hh);

            /* get tail of the reversed segment */
            auto t = get_tail(nh);

            /* set head to return if not set */
            if (head_to_return == nullptr) {
                head_to_return = nh;
            }

            if (pt) {
                pt->next = nh;
            }
            pt = t;

            c = n;
        }

        if (head_to_return == nullptr)
            head_to_return = head;

        return head;
    }
};

int main() {
    Solution sol;
    int r;

    cout << r << endl;
}
