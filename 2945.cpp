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
    int findMaximumLength(vector<int> &nums)
    {
        auto n = nums.size();
        vector<long long> sum(n + 1), prev(n + 2), dp(n + 1);

        for (int i = 1; i <= n; i++)
            sum[i] = sum[i - 1] + nums[i - 1];

        long long i = 0;
        for (int j = 1; j <= n; j++)
        {
            i = max(i, prev[j]); // if this was previously optimizesd.
            dp[j] = dp[i] + 1;

            long long k = lower_bound(sum.begin(), sum.end(), 2 * sum[j] - sum[i]) - sum.begin();
            prev[k] = j;
        }
        return dp[n];
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.findMaximumLength(vector<int>() = {272, 482, 115, 925, 983});
    cout << r << endl;

    r = sol.findMaximumLength(vector<int>() = {103, 652, 579});
    cout << r << endl;

    r = sol.findMaximumLength(vector<int>() = {4, 3, 2, 6});
    cout << r << endl;

    r = sol.findMaximumLength(vector<int>() = {1, 2, 3, 4});
    cout << r << endl;

    r = sol.findMaximumLength(vector<int>() = {5, 2, 2});
    cout << r << endl;
}