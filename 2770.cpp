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
    vector<int> dp; 

    int dfs(vector<int> &nums, int k, int target)
    {
        int n = nums.size();
        if (k == n - 1)
            return 0;

        if (dp[k] == 0)
        {
            int rv = -1e9;
            for (auto i = k; i < n; ++i)
                if (i != k && abs(nums[k] - nums[i]) <= target)
                    rv = max(rv, 1 + dfs(nums, i, target));
            dp[k] = rv + 1;
        }
        return dp[k] - 1;
    }

public:
    int maximumJumps(vector<int> &nums, int target)
    {
        dp = vector<int>(nums.size());
        int rv = dfs(nums, 0, target);
        return rv < 0 ? -1 : rv;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}