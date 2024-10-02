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
  public:
    vector<int> shortestDistanceAfterQueries(int n,
                                             vector<vector<int>>& queries) {

        set<array<int, 2>> set;
        for (auto i = 0; i < n - 1; ++i)
            set.insert({i, 1});

        vector<int> rv;
        for (auto& q : queries) {
            auto s = q[0], d = q[1];
            array<int, 2> t = {s, 0};
            auto it = lower_bound(begin(set), end(set), t);
            if (it != set.end() && (*it)[0] == s && (*it)[1] <= d - s) {
                while (it != set.end() && (*it)[0] + (*it)[1] <= d) {
                    it = set.erase(it);
                }
                set.insert({s, d - s});
            }
            rv.push_back(set.size());
        }

        return rv;
    }
};

int main() {
    Solution sol;
    vector<int> r;

    r = sol.shortestDistanceAfterQueries(
        5, vector<vector<int>>() = {{1, 4}, {2, 4}});
    for (auto& rr : r)
        cout << rr << ", ";
    cout << endl;

    r = sol.shortestDistanceAfterQueries(
        5, vector<vector<int>>() = {{2, 4}, {0, 2}, {0, 4}});
    for (auto& rr : r)
        cout << rr << ", ";
    cout << endl;
}
