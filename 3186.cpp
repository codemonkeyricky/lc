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

    vector<long long> dp;

    long long dfs(vector<array<long long, 2>>& cnt, int k) {
        int n = cnt.size();
        if (k >= n)
            return 0;

        if (dp[k] == 0) {

            long long a = 0, b = 0;
            int kk;
            for (kk = k; kk < n; ++kk)
                if (cnt[k][0] + 2 < cnt[kk][0])
                    break;

            a = cnt[k][0] * cnt[k][1] + dfs(cnt, kk);
            b = dfs(cnt, k + 1);

            dp[k] = max(a, b) + 1;
        }
        return dp[k] - 1;
    }

  public:
    long long maximumTotalDamage(vector<int>& power) {

        map<int, int> m;
        for (auto& p : power)
            ++m[p];
        vector<array<long long, 2>> cnt;
        for (auto& mm : m)
            cnt.push_back({mm.first, mm.second});

        dp = vector<long long>(cnt.size());
        return dfs(cnt, 0);
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.maximumTotalDamage(
        vector<int>() = {5, 9, 2, 10, 2, 7, 10, 9, 3, 8});
    cout << r << endl;

    r = sol.maximumTotalDamage(vector<int>() = {7, 1, 6, 6});
    cout << r << endl;

    r = sol.maximumTotalDamage(vector<int>() = {1, 1, 3, 4});
    cout << r << endl;
}
