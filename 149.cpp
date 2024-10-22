#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <climits>
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
    int maxPoints(vector<vector<int>>& points) {
        int n = points.size();

        if (n <= 1)
            return n;

        /* sort by x - makes slope calculation easier */
        sort(points.begin(), points.end());

        map<array<double, 2>, unordered_set<int>> lines;
        for (auto i = 0; i < n; ++i) {
            for (auto j = i + 1; j < n; ++j) {
                double dy = points[j][1] - points[i][1];
                double dx = points[j][0] - points[i][0];
                double a = (dx == 0) ? -1e9 : dy / dx;

                double b;
                if (dx)
                    b = points[i][1] - a * points[i][0];
                else
                    b = points[i][0];

                lines[{a, b}].insert(i);
                lines[{a, b}].insert(j);
            }
        }

        int rv = 0;
        for (auto& line : lines) {
            rv = max(rv, (int)line.second.size());
        }

        return rv;
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.maxPoints(
        vector<vector<int>>() = {{3, 3}, {1, 4}, {1, 1}, {2, 1}, {2, 2}});
    cout << r << endl;

    r = sol.maxPoints(vector<vector<int>>() = {{1, 1}, {2, 2}, {3, 3}});
    cout << r << endl;
}
