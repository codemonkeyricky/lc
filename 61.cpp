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
    ListNode* rotateRight(ListNode* head, int k) {

        auto l = 0;
        auto c = head;
        while (c) {
            c = c->next;
            ++l;
        }

        k %= l;

        /* find node to become new tail */
        int kk = 0;
        c = head;
        ListNode* nt = nullptr;
        while (c) {
            if (kk >= k) {
                if (!nt)
                    nt = head;
                else
                    nt = nt->next;
            }

            c = c->next;
            ++kk;
        }

        auto nh = nt->next;

        /* find tail node */
        auto t = head;
        while (t->next) {
            t = t->next;
        }

        t->next = head;
        nt->next = nullptr;

        return nh;
    }
};

int main() {
    Solution sol;
    int r;

    cout << r << endl;
}
