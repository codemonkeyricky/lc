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
    constexpr int static n = 100000;
    int bt[n + 1] = {};
    int query(int i) {
        int sum = 0;
        for (i = i + 1; i > 0; i -= i & (-i))
            sum += bt[i];
        return sum;
    }
    void update(int i, int val) {
        for (i = i + 1; i <= n; i += i & (-i))
            bt[i] += val;
    }

  public:
    long long goodTriplets(vector<int>& nums1, vector<int>& nums2) {
        long long rv = 0, n = nums1.size();

        /* construct value to index lookup for nums2 */
        vector<int> lookup(n);
        for (int i = 0; i < n; ++i)
            lookup[nums2[i]] = i;

        /* Iterate through nums1 but add the corresponding indices of nums2 into
         * bit. This includes all the nums1 seen so far - but with nums2 index */
        for (int i = 0; i < n - 1; ++i) {
            int m = lookup[nums1[i]];
            int smaller = query(m);
            /* number of elements after nums2 - (i - smaller) */
            int greater = (n - 1 - m) - (i - smaller);
            rv += (long long)smaller * greater;
            update(m, 1);
        }
        return rv;
    }
};

int main() {
    Solution sol;
    int r;

    cout << r << endl;
}
