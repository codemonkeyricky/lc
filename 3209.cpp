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
  public:
    long long countSubarrays(vector<int>& nums, int k) {
        unordered_map<int, int> cnt;
        auto rv = 0ll;
        for (auto& n : nums) {
            /*
             * Due to the AND property, cnt is never larger than 32
             * Once we start a new subarray, the number of bits can only reduce.
             */
            unordered_map<int, int> cnt1;
            if ((k & n) == k) {
                /* n has the same bits or more as k */
                cnt1[n] = 1;
                for (auto [v, count] : cnt) {
                    /* iterate though previously cached values and AND with
                     * them */
                    cnt1[v & n] += count;
                }
                /* only add the subarray with value k */
                rv += cnt1[k];
            }
            swap(cnt, cnt1);
        }
        return rv;
    }
};

int main() {
    Solution sol;
    int r;

    cout << r << endl;
}
