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

using ll = long long;
class Solution {
    array<ll, 2> dfs(vector<ll>& has, int mod, vector<vector<int>>& al, int u,
                     string& s, vector<ll>& pow) {
        int count = 0;
        long long hashes = 0;
        for (int v : al[u]) {
            auto [h, c] = dfs(has, mod, al, v, s, pow);
            if (count == 0) {
                hashes = h;
            } else {
                hashes = (hashes + (h * pow[count]) % mod) % mod;
            }
            count += c;
        }
        hashes = (hashes + (pow[count] * (s[u] - 'a')) % mod) % mod;
        has[u] = hashes;
        ++count;
        return {hashes, count};
    }

    array<ll, 2> dfs_rev(vector<long long>& hashes_rev, int mod,
                         vector<vector<int>>& al, int u, string& s,
                         vector<long long>& pow) {
        int count = 1;
        long long hashes = s[u] - 'a';

        for (int i = al[u].size() - 1; i >= 0; i--) {
            int v = al[u][i];
            auto [h, c] = dfs_rev(hashes_rev, mod, al, v, s, pow);

            hashes = (hashes + (h * pow[count]) % mod) % mod;
            count += c;
        }
        hashes_rev[u] = hashes;
        return {hashes, count};
    }

  public:
    vector<bool> findAnswer(vector<int>& parent, string s) {
        int n = parent.size();
        vector<ll> hashes(n, -1), hashes_rev(n, -1);
        vector<vector<int>> al(n);
        for (int i = 0; i < n; i++) {
            if (parent[i] != -1) {
                al[parent[i]].push_back(i);
            }
        }

        /* sort to satisfy traverse order requirement */
        for (int i = 0; i < n; i++)
            sort(al[i].begin(), al[i].end());

        /* pre-compute power */
        vector<ll> pow(n + 1, 1);
        for (int i = 1; i <= n; i++) {
            pow[i] = (pow[i - 1] * 31) % 1000000009;
        }

        vector<bool> rv(n, 1);

        dfs(hashes, 1000000009, al, 0, s, pow);
        dfs_rev(hashes_rev, 1000000009, al, 0, s, pow);

        for (int i = 0; i < n; i++) {
            rv[i] = hashes_rev[i] == hashes[i];
        }
        return rv;
    }
};

int main() {
    Solution sol;
    int r;

    sol.findAnswer(vector<int>() = {-1, 0, 0, 1, 1, 2}, "aababa");
}
