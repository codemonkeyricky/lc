#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cmath>
#include <functional>
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

using vi = vector<int>;
using vvi = vector<vector<int>>;
using vll = vector<long long>;
using vvll = vector<vector<long long>>;

class Solution {
  private:
    int n, u, v, dist;
    vvi al;
    vi dist_u, dist_v, rv;

  public:
    vi lastMarkedNodes(vvi& edges) {
        n = edges.size() + 1;
        al.resize(n);
        dist_u.assign(n, -1);
        dist_v.assign(n, -1);
        rv.resize(n);

        for (auto edge : edges) {
            al[edge[0]].push_back(edge[1]);
            al[edge[1]].push_back(edge[0]);
        }

        function<void(int, int, int, int&)> dfs = [&](int u, int p, int d,
                                                      int& w) -> void {
            if (d > dist) {
                dist = d;
                w = u;
            }

            for (auto& v : al[u]) {
                if (v != p) {
                    dfs(v, u, d + 1, w);
                }
            }
        };
        u = -1, dist = -1;
        dfs(0, -1, 0, u);

        v = -1, dist = -1;
        dfs(u, -1, 0, v);

        queue<int> qbfs;

        function<void(vi&)> bfs = [&](vi& dist_w) -> void {
            int d = 1;

            while (!qbfs.empty()) {
                int sz = qbfs.size();
                for (int i = 0; i < sz; i++) {
                    int node = qbfs.front();
                    for (const int i : al[node]) {
                        if (dist_w[i] != -1)
                            continue;
                        dist_w[i] = d;
                        qbfs.push(i);
                    }
                    qbfs.pop();
                }
                ++d;
            }
        };
        dist_u[u] = 0;
        qbfs.push(u);
        bfs(dist_u);
        dist_v[v] = 0;
        qbfs.push(v);
        bfs(dist_v);

        for (int i = 0; i < n; i++)
            rv[i] = (dist_u[i] > dist_v[i]) ? u : v;
        return rv;
    }
};

int main() {
    Solution sol;
    vi r;

    r = sol.lastMarkedNodes(vector<vector<int>>() = {{0, 1}, {0, 2}});
    // cout << r << endl;
}
