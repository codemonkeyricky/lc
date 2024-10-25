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
    int maximalSquare(vector<vector<char>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        vector<vector<int>> prefix(1 + m, vector<int>(n + 1));
        for (auto i = 1; i <= m; ++i) {
            for (auto j = 1; j <= n; ++j) {
                prefix[i][j] = prefix[i - 1][j] + prefix[i][j - 1] -
                               prefix[i - 1][j - 1] + matrix[i - 1][j - 1] - '0';
            }
        }

        int mmin = min(m, n);
        int rv = 0;
        for (auto k = 1; k <= mmin; ++k) {
            for (auto i = k; i <= m; ++i) {
                for (auto j = k; j <= n; ++j) {
                    int sum = prefix[i][j] - prefix[i - k][j] -
                              prefix[i][j - k] + prefix[i - k][j - k];

                    if (sum == k * k) {
                        rv = k * k;
                    }
                }
            }
        }
        return rv;
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.maximalSquare(vector<vector<char>>() = {
                              {'1', '0', '1', '0', '0'},
                              {'1', '0', '1', '1', '1'},
                              {'1', '1', '1', '1', '1'},
                              {'1', '0', '0', '1', '0'},
                          });
    cout << r << endl;
}
