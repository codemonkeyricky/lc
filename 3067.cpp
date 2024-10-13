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
    void dfs(vector<vector<array<int, 2>>>& al, int p, int u, int w, int signal,
             int& leaf) {
        if (w % signal == 0)
            ++leaf;

        for (auto& [v, ww] : al[u]) {
            if (v != p) {
                dfs(al, u, v, w + ww, signal, leaf);
            }
        }
    }

  public:
    vector<int> countPairsOfConnectableServers(vector<vector<int>>& edges,
                                               int signalSpeed) {
        int n = 0;
        for (auto& edge : edges) {
            n = max({n, edge[0], edge[1]});
        }
        ++n;

        vector<vector<array<int, 2>>> al(n);
        for (auto& e : edges) {
            al[e[0]].push_back({e[1], e[2]});
            al[e[1]].push_back({e[0], e[2]});
        }

        vector<int> rv;
        for (auto i = 0; i < n; ++i) {
            vector<int> nodes(al[i].size());
            int k = 0;
            for (auto& [v, w] : al[i]) {
                dfs(al, i, v, w, signalSpeed, nodes[k++]);
            }

            int r = 0, sum = nodes[0];
            for (auto i = 1; i < nodes.size(); ++i)
                r += nodes[i] * sum, sum += nodes[i];
            rv.push_back(r);
        }
        return rv;
    }
};

int main() {
    Solution sol;
    vector<int> r;

    r = sol.countPairsOfConnectableServers(
        vector<vector<int>>() =
            {{0, 6, 3}, {6, 5, 3}, {0, 3, 1}, {3, 2, 7}, {3, 1, 6}, {3, 4, 2}},
        3);
    for (auto& rr : r)
        cout << rr << ", ";
    cout << endl;

    r = sol.countPairsOfConnectableServers(vector<vector<int>>() = {{0, 1, 1},
                                                                    {1, 2, 5},
                                                                    {2, 3, 13},
                                                                    {3, 4, 9},
                                                                    {4, 5, 2}},
                                           1);
    for (auto& rr : r)
        cout << rr << ", ";
    cout << endl;
}
