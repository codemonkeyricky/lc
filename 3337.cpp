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

    const int MOD = 1e9 + 7;
    vector<vector<int>> mat_mul(const vector<vector<int>>& mat1,
                                const vector<vector<int>>& mat2, int mod) {
        int rows = mat1.size();
        int cols = mat2[0].size();
        int common_dim = mat2.size();
        vector<vector<int>> res(rows, vector<int>(cols, 0));

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                for (int k = 0; k < common_dim; k++) {
                    res[i][j] =
                        (res[i][j] + (1LL * mat1[i][k] * mat2[k][j]) % mod) %
                        mod;
                }
            }
        }
        return res;
    }

    vector<vector<int>> mat_pow(vector<vector<int>> mat, int n, int mod) {
        int size = mat.size();
        vector<vector<int>> res(size, vector<int>(size, 0));
        for (int i = 0; i < size; i++)
            res[i][i] = 1;

        while (n > 0) {
            if (n & 1) {
                res = mat_mul(res, mat, mod);
            }
            mat = mat_mul(mat, mat, mod);
            n >>= 1;
        }
        return res;
    }

  public:
    int lengthAfterTransformations(const string& s, int t,
                                   const vector<int>& A) {
        vector<vector<int>> M(26, vector<int>(26, 0));
        for (int i = 0; i < A.size(); ++i) {
            int k = A[i];
            for (int j = i + 1; j <= i + k; ++j) {
                M[i][j % 26] = 1;
            }
        }

        vector<vector<int>> Mt = mat_pow(M, t, MOD);
        vector<int> count(26, 0);
        for (char c : s) {
            count[c - 'a']++;
        }

        vector<vector<int>> res = mat_mul({count}, Mt, MOD);
        int sum_result = 0;
        for (int val : res[0]) {
            sum_result = (sum_result + val) % MOD;
        }

        return sum_result;
    }
};

int main() {
    Solution sol;
    int r;

    // r = sol.lengthAfterTransformations(
    //     "azbk", 3, vector<int>() = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    //     2,
    //                                 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    //                                 2});
    // cout << r << endl;

    // r = sol.lengthAfterTransformations(
    //     "azbk", 2, vector<int>() = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    //     2,
    //                                 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    //                                 2});
    // cout << r << endl;

    // r = sol.lengthAfterTransformations(
    //     "azbk", 1, vector<int>() = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    //     2,
    //                                 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    //                                 2});
    // cout << r << endl;

    r = sol.lengthAfterTransformations(
        "abcyy", 52, vector<int>() = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2});
    cout << r << endl;

    r = sol.lengthAfterTransformations(
        "abcyy", 26, vector<int>() = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2});
    cout << r << endl;

    r = sol.lengthAfterTransformations(
        "abcyy", 2, vector<int>() = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                     1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2});
    cout << r << endl;
}
