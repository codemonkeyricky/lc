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

class NumArray {

    vector<int> bit;

    int query(int k) {
        int rv = 0;
        /* k is internally +1 */
        /* query from right to left */
        for (++k; k; k -= k & -k) {
            rv += bit[k];
        }
        return rv;
    }

    void update_bit(int k, int v) {
        for (++k; k < bit.size(); k += k & -k)
            bit[k] += v;
    }

  public:
    NumArray(vector<int>& nums) {
        int n = nums.size();

        bit = vector<int>(n + 1);

        for (auto i = 0; i < n; ++i) {
            update_bit(i, nums[i]);
        }
    }

    void update(int index, int val) {
        int a = query(index);
        int b = 0;
        if (index)
            b = query(index - 1);
        update_bit(index, -(a - b));
        update_bit(index, val);
    }

    int sumRange(int left, int right) {
        int a = query(right);
        int b = 0;
        if (left)
            b = query(left - 1);

        return a - b;
    }
};

int main() {
    vector<int> a = {0, 0, 1, 0, 0};
    NumArray aa(a);
    aa.sumRange(0, 5);
}
