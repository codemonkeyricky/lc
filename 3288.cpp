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
    int maxPathLength(vector<vector<int>>& coords, int k) {
        int x = coords[k][0], y = coords[k][1];
        /* sort x ascending but y descending */
        sort(begin(coords), end(coords), [](const auto& a, const auto& b) {
            return a[0] == b[0] ? a[1] > b[1] : a[0] < b[0];
        });

        /*
         * separate between before and after
         * for the same x, we want to iterate from largest y to smallest y
         * as we iterate through x, the order is gauranteed to be increasing, so
         * we just need to sort through y
         */

        vector<int> before, after;
        for (const auto& c : coords)
            if (c[0] < x && c[1] < y)
                insertLIS(before, c[1]);
            else if (c[0] > x && c[1] > y)
                insertLIS(after, c[1]);
        return 1 + before.size() + after.size();
    }
    void insertLIS(vector<int>& ms, int y) {
        if (auto it = lower_bound(begin(ms), end(ms), y); it == end(ms))
            ms.push_back(y);
        else
            *it = y;
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.maxPathLength(
        vector<vector<int>>() = {{9, 6}, {8, 3}, {3, 2}, {3, 5}}, 0);
    cout << r << endl;

    r = sol.maxPathLength(vector<vector<int>>() = {{0, 3}, {8, 5}, {6, 8}}, 0);
    cout << r << endl;

    r = sol.maxPathLength(vector<vector<int>>() = {{2, 1}, {7, 0}, {5, 6}}, 2);
    cout << r << endl;

    r = sol.maxPathLength(
        vector<vector<int>>() = {{3, 1}, {2, 2}, {4, 1}, {0, 0}, {5, 3}}, 1);
    cout << r << endl;
}
