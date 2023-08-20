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
    long long dp[100001][2] = {};
    long long dfs(vector<int> &nums, int x, int k, int parity)
    {
        if (k >= nums.size())
            return 0;

        if (!dp[k][parity])
        {
            long long a = nums[k] + dfs(nums, x, k + 1, nums[k] & 1) - x * (parity ^ (nums[k] & 1));
            long long b = dfs(nums, x, k + 1, parity);
            dp[k][parity] = max(a, b);
        }
        return dp[k][parity];
    }

public:
    long long maxScore(vector<int> &nums, int x)
    {
        return nums[0] + dfs(nums, x, 1, nums[0] & 1);
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}