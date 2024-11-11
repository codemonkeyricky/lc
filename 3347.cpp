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
    int maxFrequency(vector<int>& nums, int k, int numOperations) {
        map<int, int> operable;
        unordered_map<int, int> cnt;
        set<int> points;
        for (auto& n : nums) {
            /* increase occurence count */
            ++cnt[n];

            /* update range */
            ++operable[n - k];
            --operable[n + k + 1];

            /* points to evaluate later */
            points.insert(n);
            points.insert(n - k);
            points.insert(n + k + 1);
        }

        int rv = 1;
        /* iterate through all points */
        int sum = 0;
        for (auto& p : points) {
            sum += operable[p];
            /* sum - cnt[p] == number of elements that can be updated */
            rv = max(rv, cnt[p] + min(sum - cnt[p], numOperations));
        }
        return rv;
    }
};

int main() {
    Solution sol;
    int r;

    cout << r << endl;
}
