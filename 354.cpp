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
    int maxEnvelopes(vector<vector<int>>& envs) {

        sort(envs.begin(), envs.end(),
             [](const vector<int>& l, const vector<int>& r) {
                 if (l[0] == r[0])
                     return l[1] > r[1];
                 return l[0] < r[0];
             });

        vector<int> a;
        for (auto& env : envs) {
            int aa = env[1];
            auto it = lower_bound(a.begin(), a.end(), aa);
            if (it == a.end()) {
                a.push_back(aa);
            } else {
                *it = aa; 
            }
        }

        return a.size();
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.maxEnvelopes(vector<vector<int>>() = {
                             {1, 3}, {3, 5}, {6, 7}, {6, 8}, {8, 4}, {9, 5}});
    cout << r << endl;

    r = sol.maxEnvelopes(
        vector<vector<int>>() = {{30, 50}, {12, 2}, {3, 4}, {12, 15}});
    cout << r << endl;

    r = sol.maxEnvelopes(
        vector<vector<int>>() = {{5, 4}, {6, 4}, {6, 7}, {2, 3}});
    cout << r << endl;
}
