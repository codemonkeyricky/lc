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
#include <climits>

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
    long long minCost(vector<int> &nums, vector<int> &costs)
    {
        int n = nums.size();
        vector<int> stack;
        vector<int> jump(n), jump2(n);
        for (auto i = 0; i < n; ++i)
        {
            while (stack.size() && nums[stack.back()] <= nums[i])
                jump[stack.back()] = i, stack.pop_back();
            stack.push_back(i);
        }

        stack.clear();
        for (auto i = 0; i < n; ++i)
        {
            while (stack.size() && nums[stack.back()] > nums[i])
                jump2[stack.back()] = i, stack.pop_back();
            stack.push_back(i);
        }

        vector<long long> dp(n, LONG_MAX);
        dp[0] = 0;
        for (auto i = 0; i < n; ++i)
        {
            if (jump[i])
                dp[jump[i]] = min(dp[jump[i]], dp[i] + costs[jump[i]]);

            if (jump2[i])
                dp[jump2[i]] = min(dp[jump2[i]], dp[i] + costs[jump2[i]]);
        }

        return dp[n - 1];
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minCost(vector<int>() = {0, 1, 2}, vector<int>() = {1, 1, 1});
    cout << r << endl;

    r = sol.minCost(vector<int>() = {3, 2, 4, 4, 1}, vector<int>() = {3, 7, 6, 4, 2});
    cout << r << endl;
}