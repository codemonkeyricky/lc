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
    int validSubarraySplit(vector<int> &nums)
    {
        int n = nums.size();
        vector<vector<int>> dp(n + 1, vector<int>(n + 1));

        for (auto i = 0; i < n; ++i)
            for (auto j = i; j < n; ++j)
                dp[i][j] = __gcd(nums[i], nums[j]) > 1 ? 1 : 1e9;

        for (auto j = 0; j < n; ++j)
            for (auto i = 0; i < j; ++i)
                dp[0][j] = min(dp[0][j], dp[0][i] + dp[i + 1][j]);

        return dp[0][n - 1] != 1e9 ? dp[0][n - 1] : -1;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.validSubarraySplit(vector<int>() = {29, 5, 59, 73, 89, 31, 73, 89, 73, 79, 89, 89, 23, 53, 43, 47, 3, 2, 61, 7});
    cout << r << endl;

    r = sol.validSubarraySplit(vector<int>() = {1, 2, 1});
    cout << r << endl;

    r = sol.validSubarraySplit(vector<int>() = {3, 5});
    cout << r << endl;

    r = sol.validSubarraySplit(vector<int>() = {2, 6, 3, 4, 3});
    cout << r << endl;
}