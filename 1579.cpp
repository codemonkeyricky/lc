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
  private:
    int find(vector<int>& parents, int k) {
        if (parents[k] < 0)
            return k;

        return parents[k] = find(parents, parents[k]);
    }

    bool unionize(vector<int>& parents, int i, int j) {
        auto p1 = find(parents, i);
        auto p2 = find(parents, j);
        if (p1 != p2) {
            if (parents[p1] > parents[p2])
                swap(p1, p2);
            parents[p1] += parents[p2];
            parents[p2] = p1;
            return true;
        }
        return false;
    }

  public:
    int maxNumEdgesToRemove(int n, vector<vector<int>>& edges) {
        sort(begin(edges), end(edges), greater<vector<int>>());

        int i;
        vector<int> parents(n + 1, -1);
        int rv = 0;
        for (i = 0; i < edges.size() && edges[i][0] == 3; i++) {
            if (!unionize(parents, edges[i][1], edges[i][2]))
                ++rv;
        }

        vector<int> copy = parents;
        for (; i < edges.size() && edges[i][0] == 2; i++) {
            if (!unionize(parents, edges[i][1], edges[i][2]))
                ++rv;
        }
        if (abs(parents[find(parents, 1)]) < n)
            return -1;

        parents = copy;
        for (; i < edges.size(); i++) {
            if (edges[i][0] != 1)
                break;

            auto p1 = find(parents, edges[i][1]);
            auto p2 = find(parents, edges[i][2]);
            if (p1 != p2) {
                if (parents[p1] > parents[p2])
                    swap(p1, p2);
                parents[p1] += parents[p2];
                parents[p2] = p1;
            } else {
                rv++;
            }
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
