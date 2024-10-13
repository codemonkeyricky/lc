#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
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

#define ll long long
void print(vector<vector<ll>>& dp) {
    int m = dp.size(), n = dp[0].size();
    for (auto i = 0; i < m; ++i) {
        for (auto j = 0; j < n; ++j)
            printf("%lld ", dp[i][j]);
        printf("\n");
    }
}

class Solution {
  public:
    const int M = 1e9 + 7;
    int numberOfStableArrays(int zero, int one, int limit) {
        long long dp[zero + 1][one + 1][2];
        memset(dp, 0, sizeof(dp));

        /* dp zero/one/ending */
        dp[0][0][0] = 1;
        dp[0][0][1] = 1;

        for (int z = 0; z <= zero; z++) {
            for (int o = 0; o <= one; o++) {
                if (z || o) {
                    if (z < limit) {
                        if (z > 0) {
                            dp[z][o][1] = dp[z - 1][o][0];
                            if (z > 1) {
                                dp[z][o][1] += dp[z - 1][o][1];
                            }
                        }
                    } else if (z == limit) {
                        if (z > 0) {
                            dp[z][o][1] = dp[z - 1][o][0];
                            if (limit > 1) {
                                dp[z][o][1] += dp[z - 1][o][1];
                            }
                        }
                    } else if (z > limit) {
                        dp[z][o][1] = dp[z - 1][o][0];
                        if (limit > 1) {
                            dp[z][o][1] +=
                                dp[z - 1][o][1] - dp[z - 1 - limit][o][0];
                        }
                    }
                    dp[z][o][1] %= M;
                    dp[z][o][1] += M;
                    dp[z][o][1] %= M;

                    if (o < limit) {
                        if (o > 0) {
                            dp[z][o][0] = dp[z][o - 1][1];
                            if (o > 1) {
                                dp[z][o][0] += dp[z][o - 1][0];
                            }
                        }
                    } else if (o == limit) {
                        if (o > 0) {
                            dp[z][o][0] = dp[z][o - 1][1];
                            if (limit > 1) {
                                dp[z][o][0] += dp[z][o - 1][0];
                            }
                        }
                    } else if (o > limit) {
                        dp[z][o][0] = dp[z][o - 1][1];
                        if (limit > 1) {
                            dp[z][o][0] +=
                                dp[z][o - 1][0] - dp[z][o - 1 - limit][1];
                        }
                    }
                    dp[z][o][0] %= M;
                    dp[z][o][0] += M;
                    dp[z][o][0] %= M;
                }
            }
        }
        return (dp[zero][one][0] + dp[zero][one][1]) % M;
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.numberOfStableArrays(1, 2, 1);
    cout << r << endl;

    r = sol.numberOfStableArrays(3, 3, 2);
    cout << r << endl;
}
