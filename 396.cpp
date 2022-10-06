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
    int maxRotateFunction(vector<int> &nums)
    {
        int n = nums.size();

        int mul = 0;
        for (auto i = 0; i < n; ++i)
            mul += i * nums[i];

        auto sum = accumulate(begin(nums), end(nums), 0);
        vector<int> dp(n);
        for (auto i = 0; i < n; ++i)
            dp[i] = sum - nums[i];
        
        int rv = mul;
        for (int i = n - 1; i >= 0; --i)
        {
            mul = mul - nums[i] * (n - 1) + dp[i];
            rv = max(rv, mul);
        }

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.maxRotateFunction(vector<int>() = {4, 3, 2, 6});
    cout << r << endl;
}