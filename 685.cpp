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

    int find(vector<int>& parents, int k) {
        if (parents[k] < 0)
            return k;
        return parents[k] = find(parents, parents[k]);
    }

  public:
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        int n = edges.size();

        vector<int> p(n + 1), a, b;
        for (auto& e : edges) {
            if (p[e[1]] == 0)
                p[e[1]] = e[0];
            else {
                a = {p[e[1]], e[1]};
                b = e, e[1] = 0;
            }
        }

        vector<int> parents(n + 1, -1);
        for (auto& e : edges) {
            auto u = e[0], v = e[1];
            auto p = find(parents, u);

            if (p == v)
                if (a.empty())
                    return e;
                else
                    return a;

            parents[p] += parents[v];
            parents[v] = p;
        }

        return b;
    }
};

int main() {
    Solution sol;
    int r;

    cout << r << endl;
}
