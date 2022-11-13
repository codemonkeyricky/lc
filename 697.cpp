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
    int findShortestSubArray(vector<int> &nums)
    {
        vector<array<int, 2>> dp(50001);
        int freq = 0, rv = 1;
        for (auto i = 0; i < nums.size(); ++i)
        {
            if (dp[nums[i]][1] == 0)
                dp[nums[i]][0] = i;

            if (++dp[nums[i]][1] > freq)
                rv = i - dp[nums[i]][0] + 1, freq = dp[nums[i]][1];
            else if (dp[nums[i]][1] == freq)
                rv = min(rv, i - dp[nums[i]][0] + 1);
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.findShortestSubArray(vector<int>() = {1, 2, 2, 3, 1});
    cout << r << endl;

    r = sol.findShortestSubArray(vector<int>() = {1, 1});
    cout << r << endl;
}