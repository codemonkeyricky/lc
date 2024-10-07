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

class Solution {
  public:
    int maximumSetSize(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        int target = n / 2;
        set<int> s1(nums1.begin(), nums1.end()), s2(nums2.begin(), nums2.end());

        /* n1 and n2 represent elements cut from nums1 and nums2 */
        int n1 = max(0, n - (int)s1.size());
        int n2 = max(0, n - (int)s2.size());

        set<int> r;
        set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(),
                         inserter(r, r.begin()));

        int common = r.size();
        if (n1 < target) {
            int trim = min(target - n1, common);
            common -= trim;
            n1 += trim;
        }

        if (n2 < target) {
            int trim = min(target - n2, common);
            common -= trim;
            n2 += trim;
        }

        int t1 = max(0, target - n1);
        int t2 = max(0, target - n2);

        r.clear();
        set_union(s1.begin(), s1.end(), s2.begin(), s2.end(),
                  inserter(r, r.begin()));

        return r.size() - t1 - t2;
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.maximumSetSize(vector<int>() = {1, 1, 2, 2, 3, 3},
                           vector<int>() = {4, 4, 5, 5, 6, 6});
    cout << r << endl;

    r = sol.maximumSetSize(vector<int>() = {1, 2, 3, 4, 5, 6},
                           vector<int>() = {2, 3, 2, 3, 2, 3});
    cout << r << endl;

    r = sol.maximumSetSize(vector<int>() = {1, 2, 1, 2},
                           vector<int>() = {1, 1, 1, 1});
    cout << r << endl;
}
