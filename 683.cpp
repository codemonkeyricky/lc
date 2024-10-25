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

class Solution {
    int N = 0;

    vector<int> bit;

    void update(int k) {
        for (; k < N; k += k & -k) {
            ++bit[k];
        }
    }

    int query(int k) {
        int rv = 0;
        for (; k; k -= k & -k) {
            rv += bit[k];
        }
        return rv;
    }

  public:
    int kEmptySlots(vector<int>& bulbs, int k) {
        N = bulbs.size() + 1;
        bit = vector<int>(N);

        for (auto i = 0; i < bulbs.size(); ++i) {
            if (bulbs[i] >= k + 1) {
                int a = query(bulbs[i]);
                int b = query(bulbs[i] - k - 1);

                if (a && a == b)
                    return i + 1;
            }
            update(bulbs[i]);
        }

        return -1;
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.kEmptySlots(vector<int>() = {1, 3, 2}, 1);
    cout << r << endl;
}
