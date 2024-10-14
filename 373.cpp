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
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2,
                                       int k) {
        int n = nums1.size(), m = nums2.size();

        if (!n || !m)
            return {};

        priority_queue<array<int, 3>> q;

        set<array<int, 2>> seen;
        q.push({-nums1[0] - nums2[0], 0, 0});
        seen.insert({0, 0});
        vvi rv;
        while (k) {

            auto [s, i, j] = q.top();
            q.pop();

            rv.push_back({nums1[i], nums2[j]});

            if (i + 1 < nums1.size() && !seen.count({i + 1, j})) {
                q.push({-(nums1[i + 1] + nums2[j]), i + 1, j});
                seen.insert({i + 1, j});
            }

            if (j + 1 < nums2.size() && !seen.count({i, j + 1})) {
                q.push({-(nums1[i] + nums2[j + 1]), i, j + 1});
                seen.insert({i, j + 1});
            }

            --k;
        }

        return rv;
    }
};

int main() {
    Solution sol;
    int r;

    sol.kSmallestPairs(vi() = {1, 2, 4, 5, 6}, vi() = {3, 5, 7, 9}, 20);
}
