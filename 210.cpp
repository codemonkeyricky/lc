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

    int dfs(vector<vector<int>>& al, int u, vector<int>& dp) {
        if (dp[u] == 0) {
            int rv = 1;
            for (auto v : al[u]) {
                rv += dfs(al, v, dp);
            }
            dp[u] = rv;
        }
        return dp[u];
    }

    int dfs2(vector<vector<int>>& al, int u, vector<int>& rv) {

        rv.push_back()

    }

  public:
    vector<int> findOrder(int n, vector<vector<int>>& prerequisites) {
        vector<vector<int>> al(n);

        for (auto& p : prerequisites) {
            al[p[1]].push_back(p[0]);
        }

        vector<int> dp(n);
        for (auto i = 0; i < n; ++i) {
            dfs(al, i, dp);
        }
    }
};

int main() {
    Solution sol;
    int r;

    cout << r << endl;
}
