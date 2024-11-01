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

    /*
     * parents[] represents the membership of every node
     * parent[k] == 0   -> invalid
     * parent[k] == -x  -> k is the root node with x members
     * parent[k] == x   -> x is parent of node k
     *
     * parents[] is initialized to {-1, -1, -1, -1, ... }
     * parents[] of {-3, 0, 0, -1} means node 0/1/2 are in the same membership,
     * and node 3 is in its own membership.
     */

    /* find parent of the node */
    int find(vector<int>& parents, int k) {
        if (parents[k] < 0)
            return k;
        /* path compression as we perform find */
        return parents[k] = find(parents, parents[k]);
    }

    /* join membership between i and j - add the smaller group to the larger
     * group to minimize path compression cost */
    bool unionize(vector<int>& parents, int i, int j) {
        auto p1 = find(parents, i);
        auto p2 = find(parents, j);
        /* only join if the two are in separate groups */
        if (p1 != p2) {
            /* always join the smaller group to the larger group - swap if
             * needed */
            if (parents[p1] > parents[p2])
                swap(p1, p2);

            /* increase member count of the larger group */
            parents[p1] += parents[p2];

            /* update parent pointer of the smaller group to point towards the
             * larger group */
            parents[p2] = p1;
            return true;
        }
        return false;
    }

  public:
    int maxNumEdgesToRemove(int n, vector<vector<int>>& edges) {

        /* The given graph is assumed to be complete (ie. alice and bob can
         * traverse to all nodes). The goal is to find all redundant edges to
         * remove. */

        /* process type 3 connections first */
        sort(begin(edges), end(edges), greater<vector<int>>());

        /* process two way roads first, drop any redundant */
        int i;
        vector<int> parents(n + 1, -1);
        int rv = 0;
        for (i = 0; i < edges.size() && edges[i][0] == 3; i++) {
            if (!unionize(parents, edges[i][1], edges[i][2]))
                ++rv;
        }

        /* process roads only bob can use */
        vector<int> copy = parents;
        for (; i < edges.size() && edges[i][0] == 2; i++) {
            /* since we added all the two way roads already, any repeated
             * connection can be dropped */
            if (!unionize(parents, edges[i][1], edges[i][2]))
                ++rv;
        }
        if (abs(parents[find(parents, 1)]) < n)
            return -1;

        /* process roads only alice can use */
        parents = copy;
        for (; i < edges.size(); i++) {
            /* since we added all the two way roads already, any repeated
             * connection can be dropped */
            if (!unionize(parents, edges[i][1], edges[i][2]))
                ++rv;
        }

        if (abs(parents[find(parents, 1)]) < n)
            return -1;

        return rv;
    }
};

int main() {
    Solution sol;
    int r;

    cout << r << endl;
}
