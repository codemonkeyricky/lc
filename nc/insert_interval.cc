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
    vector<vector<int>> insert(vector<vector<int>>& intervals,
                               vector<int>& newInterval) {

        map<int, int> dp;
        for (auto& interval : intervals) {
            ++dp[interval[0]];
            --dp[interval[1]];
        }
        ++dp[newInterval[0]];
        --dp[newInterval[1]];

        vector<vector<int>> rv;
        int sum = 0, l = 0, r = 0;
        for (auto& d : dp) {
            int psum = sum;
            sum += d.second;
            if (psum == 0) {
                l = d.first;
            }
            if (sum == 0) {
                rv.push_back({l, d.first});
            }
        }

        return rv;
    }
};

int main() {
    Solution sol;
    int r;

    sol.insert(vector<vector<int>>() = {{1, 2}, {3, 4}},
               vector<int>() = {2, 3});
}
