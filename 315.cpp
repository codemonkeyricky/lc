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
    void update(int k) {
        for (; k < 20002; k += k & -k)
            bit[k]++;
    }

    int query(int k) {
        int rv = 0;
        for (; k; k -= k & -k)
            rv += bit[k];
        return rv;
    }
    vector<int> bit;

  public:
    vector<int> countSmaller(vector<int>& nums) {
        bit = vector<int>(20002);
        int n = nums.size();
        vector<int> rv(n);
        for (int i = n - 1; i >= 0; --i) {
            update(nums[i] + 10001);
            int cnt = query(nums[i] + 10001 - 1);
            rv[i] = cnt;
        }
        return rv;
    }
};

int main() {
    Solution sol;
    int r;

    cout << r << endl;
}
