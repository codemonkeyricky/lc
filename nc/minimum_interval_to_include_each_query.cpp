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
  public:
    vector<int> minInterval(vector<vector<int>>& intervals,
                            vector<int>& queries) {

        /* sort based on length */
        priority_queue<array<int, 3>> q;
        for (auto& interval : intervals) {
            q.push({interval[0] - interval[1] - 1, interval[0], interval[1]});
        }

        set<array<int, 2>> qq;
        for (auto i = 0; i < queries.size(); ++i) {
            qq.insert({queries[i], i});
        }

        vector<int> rv(queries.size(), -1);
        while (q.size()) {
            /* pop */
            auto [n, l, r] = q.top();
            q.pop();

            array<int, 2> target = {l, -1};
            auto it = qq.lower_bound(target);
            while (it != qq.end() && (*it)[0] <= r) {
                rv[(*it)[1]] = -n;
                it = qq.erase(it);
            }
        }

        return rv;
    }
};

int main() {
    Solution sol;
    vi r;

    r = sol.minInterval(
        vector<vector<int>>() = {{1, 3}, {2, 3}, {3, 7}, {6, 6}},
        vector<int>() = {2, 3, 1, 7, 6, 8});
    pvi(r);
}
