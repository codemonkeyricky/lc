#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <climits>
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
    long long minimumCost(string source, string target, vector<char>& original,
                          vector<char>& changed, vector<int>& cost) {

        // floyd warshall
        array<array<long long, 26>, 26> dp = {};
        for (auto i = 0; i < 26; ++i)
            for (auto j = 0; j < 26; ++j) {
                dp[i][j] = 1e12;
                if (i == j)
                    dp[i][j] = 0;
            }

        for (auto k = 0; k < original.size(); ++k) {
            int i = original[k] - 'a';
            int j = changed[k] - 'a';
            dp[i][j] = min(dp[i][j], (long long)cost[k]);
        }

        for (auto k = 0; k < 26; ++k)
            for (auto i = 0; i < 26; ++i)
                for (auto j = 0; j < 26; ++j)
                    if (dp[i][j] > dp[i][k] + dp[k][j])
                        dp[i][j] = dp[i][k] + dp[k][j];

        long long rv = 0;
        for (auto k = 0; k < source.size(); ++k) {
            int i = source[k] - 'a';
            int j = target[k] - 'a';

            if (dp[i][j] == 1e12)
                return -1;

            rv += dp[i][j];
        }

        return rv;
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.minimumCost("abcd", "acbe",
                        vector<char>() = {'a', 'b', 'c', 'c', 'e', 'd'},
                        vector<char>() = {'b', 'c', 'b', 'e', 'b', 'e'},
                        vector<int>() = {2, 5, 5, 1, 2, 20});
    cout << r << endl;
}
