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

    int dfs(vector<vector<int>> &al, int u, vector<int> &seen,
            vector<int> &rv) {
        if (seen[u] == 1)
            return 0;

        if (seen[u] == 2)
            return -1;

        seen[u] = 2;
        for (auto v : al[u]) {
            if (dfs(al, v, seen, rv) == -1)
                return -1;
        }
        rv.push_back(u);
        seen[u] = 1;

        return 0;
    }

public:
    vector<int> canFinish(int n, vector<vector<int>> &prereq) {

        vector<vector<int>> al(n);
        vector<int> is_leaf(n, 1);
        for (auto &p : prereq) {
            /* p1 is prereq to p0 */
            al[p[0]].push_back(p[1]);
            /* p0 cannot be a start point */
            is_leaf[p[1]] = 0;
        }

        vector<int> rv, seen(n);
        for (auto i = 0; i < n; ++i) {
            if (is_leaf[i]) {
                if (dfs(al, i, seen, rv) == -1)
                    return {};
            }
        }

        if (rv.size() != n)
            return 0; 
        return 1;
    }
};


int main() {
    Solution sol;
    int r;

    cout << r << endl;
}
