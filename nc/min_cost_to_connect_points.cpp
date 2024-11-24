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

    vector<int> parents;

    int find(int k) {
        if (parents[k] < 0)
            return k;
        return parents[k] = find(parents[k]);
    }

    void unionize(int i, int j) {

        auto p1 = find(i);
        auto p2 = find(j);
        if (p1 != p2) {
            if (parents[p1] > parents[p2])
                swap(p1, p2);
            parents[p1] += parents[p2];
            parents[p2] = p1;
        }
    }

  public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        priority_queue<array<int, 3>> q;
        int n = points.size();
        for (auto i = 0; i < n; ++i) {
            for (auto j = i + 1; j < n; ++j) {
                q.push({-abs(points[i][0] - points[j][0]) -
                        abs(points[i][1] - points[j][1])});
            }
        }

        parents = vector<int>(n, -1);
        int rv = 0;
        while (q.size()) {
            auto [n, i, j] = q.top();
            q.pop();

            if (find(i) != find(j)) {
                rv += n;
                unionize(i, j);
            }
        }
        return rv;
    }
};

int main() {
    Solution sol;
    int r;

    cout << r << endl;
}
