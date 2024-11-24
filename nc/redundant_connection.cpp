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
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        parents = vector<int>(n + 1, -1);
        vector<int> rv;
        for (auto& edge : edges) {
            int i = edge[0], j = edge[1];
            if (find(i) != find(j)) {
                unionize(i, j);
            } else {
                rv = {i, j};
            }
        }
        return rv;
    }
};

int main() {
    Solution sol;

    sol.findRedundantConnection(vector<vector<int>>() = {{9, 10},
                                                         {5, 8},
                                                         {2, 6},
                                                         {1, 5},
                                                         {3, 8},
                                                         {4, 9},
                                                         {8, 10},
                                                         {4, 10},
                                                         {6, 8},
                                                         {7, 9}});
}
