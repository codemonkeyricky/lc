#include <iostream>
#include <vector>
#include <cassert>
#include <stack>
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <bitset>
#include <numeric>
#include <cmath>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

TreeNode *recurse(vector<int> &tree, int k)
{
    if (k >= tree.size() || tree[k] == -1)
        return nullptr;

    return new TreeNode(tree[k], recurse(tree, k * 2 + 1), recurse(tree, k * 2 + 2));
}

TreeNode *populate(vector<int> &tree)
{
    return recurse(tree, 0);
}

// // Base case
//         for (auto i = 0; i < n; ++i)
//             for (auto j = i; j < n; ++j)
//                 dp[0][i][j] = j - i + 1;

//         for (auto k = 1; k < 3; ++k)
//             for (auto j = 0; j < n; ++j)
//                 for (int i = j - 2 * k; i >= 0; --i)
//                 {
//                     // dp[k][i][j] = dp[k][i][j - 1];
//                     if (s[j] == s[i])
//                         dp[k][i][j] += dp[k - 1][i + 1][j - 1];
//                 }

//         // int rv = 0;
//         // for (auto &d : dp[2])
//         //     rv += accumulate(begin(d), end(d), 0);

//         return dp[2][0][n - 1];

class Solution
{
public:
    int countPalindromes(string s)
    {
        int n = s.size();
        vector<vector<int>> left(n, vector<int>(100));
        for (auto j = 0; j < n; ++j)
        {
            if (j)
                left[j] = left[j - 1];
            for (auto i = 0; i < j; ++i)
                ++left[j][((s[i] - '0') * 10) + (s[j] - '0')];
        }

        vector<vector<int>> right(n, vector<int>(100));
        for (int i = n - 1; i >= 0; --i)
        {
            if (i + 1 < n)
                right[i] = right[i + 1];
            for (int j = n - 1; j > i; --j)
                ++right[i][((s[j] - '0') * 10) + (s[i] - '0')];
        }

        long long rv = 0;
        for (auto k = 2; k + 2 < n; ++k)
            for (auto i = 0; i < 100; i++)
                rv = (rv + (long long)left[k - 1][i] * (long long)right[k + 1][i]) % 1000000007;

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    // r = sol.countPalindromes("99999");
    // cout << r << endl;

    // r = sol.countPalindromes("9999900000");
    // cout << r << endl;

    r = sol.countPalindromes("103301");
    cout << r << endl;

    r = sol.countPalindromes("0000000");
    cout << r << endl;
}