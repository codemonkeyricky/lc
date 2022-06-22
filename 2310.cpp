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

    int dfs(vector<int> &nums, int sum)
    {
        if (sum < 0)
            return -1e9;

        if (sum == 0)
            return 0;

        if (!dp[sum])
        {
            int rv = -1e9;
            for (auto &n : nums)
            {
                rv = 1 + dfs(nums, sum - n);
                if (rv > 0)
                    break;
            }

            dp[sum] = (rv > 0 ? rv : -1e9) + 1;
        }
        return dp[sum] - 1;
    }

public:
    int minimumNumbers(int num, int k)
    {
        if (!num)
            return 0;

        if (k % 2 == 0 && num % 2)
            return -1;

        vector<int> nums;
        for (int i = 0; i <= num; ++i)
            if (i && i % 10 == k)
                nums.push_back(i);

        dp = vector<int>(3001);
        reverse(begin(nums), end(nums));
        int rv = dfs(nums, num);
        return rv > 0 ? rv : -1;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minimumNumbers(947, 2);
    cout << r << endl;

    r = sol.minimumNumbers(4, 0);
    cout << r << endl;

    r = sol.minimumNumbers(58, 9);
    cout << r << endl;
}