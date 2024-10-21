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
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        vector<int> mono;

        int rv = 0;
        for (auto j = 0; j <= n; ++j) {

            /*
             * j is current right index 
             * i is left index considered 
             * h is current height considered
             * 
             * Largest rectangle evaluated during monostack pop.
             */

            while (mono.size() &&
                   /* account for termination condition (ie. j == n)  */
                   (j >= n || heights[mono.back()] > heights[j])) {

                int h = heights[mono.back()];
                mono.pop_back();

                /* account for empty monotone stack */
                int i = mono.size() ? mono.back() : -1;

                rv = max(rv, ((j - 1) - i) * h);
            }

            if (j < n)
                mono.push_back(j);
        }

        return rv;
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.largestRectangleArea(vector<int>() = {2, 1, 2});
    cout << r << endl;

    r = sol.largestRectangleArea(vector<int>() = {0, 9});
    cout << r << endl;

    r = sol.largestRectangleArea(vector<int>() = {1});
    cout << r << endl;

    r = sol.largestRectangleArea(vector<int>() = {2, 4});
    cout << r << endl;

    r = sol.largestRectangleArea(vector<int>() = {2, 1, 5, 6, 2, 3});
    cout << r << endl;
}
