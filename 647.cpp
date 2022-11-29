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

class Solution
{
public:
    int countSubstrings(string s)
    {
        int n = s.size(), rv = 0;

        if (n <= 0)
            return 0;

        int dp[1001][1001] = {};

        // Base case: single letter substrings
        for (int i = 0; i < n; ++i, ++rv)
            dp[i][i] = true;

        // Base case: double letter substrings
        for (int i = 0; i < n - 1; ++i)
        {
            dp[i][i + 1] = (s[i] == s[i + 1]);
            rv += dp[i][i + 1];
        }

        // All other cases: substrings of length 3 to n
        for (int l = 3; l <= n; ++l)
            for (int i = 0, j = i + l - 1; j < n; ++i, ++j)
            {
                dp[i][j] = dp[i + 1][j - 1] && (s[i] == s[j]);
                rv += dp[i][j];
            }

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}