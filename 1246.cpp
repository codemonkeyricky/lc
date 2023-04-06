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
    vector<vector<int>> dp;

    int dfs(vector<int> &A, int i, int j)
    {
        if (i == j)
            return 1;

        if (i > j)
            return 0;

        if (!dp[i][j])
        {
            int rv = 1 + dfs(A, i + 1, j);
            for (int k = i + 1; k <= j; k++)
            {
                if (A[k] == A[i])
                {
                    // this is because of palindromes with length = 2 where deleting it
                    // would yield nothing so we have to manually record the deletion here
                    int left = max(1, dfs(A, i + 1, k - 1));
                    int right = dfs(A, k + 1, j);
                    rv = min(rv, left + right);
                }

                dp[i][j] = rv;
            }
            return dp[i][j];
        }
    }

public:
    int minimumMoves(vector<int> &nums)
    {
        int n = nums.size();
        dp = vector<vector<int>>(n, vector<int>());
        return dfs(nums, 0, n - 1);
    }
}

int
main()
{
    Solution sol;
    int r;

    cout << r << endl;
}