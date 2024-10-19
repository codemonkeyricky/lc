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

    void dfs(vector<int>& candidate, int k, int sum, vector<int>& curr,
             vector<vector<int>>& rv) {
        if (sum <= 0) {
            if (sum == 0)
                rv.push_back(curr);
            return;
        }

        int n = candidate.size();
        for (auto i = k; i < n; ++i) {
            curr.push_back(candidate[i]);
            dfs(candidate, i, sum - candidate[i], curr, rv);
            curr.pop_back();
        }
    }

  public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {

        vector<vector<int>> rv;
        dfs(candidates, 0, target, vector<int>() = {}, rv);
        return rv;
    }
};

int main() {
    Solution sol;
    int r;

    sol.combinationSum(vector<int>() = {2, 3, 6, 7}, 7);
}
