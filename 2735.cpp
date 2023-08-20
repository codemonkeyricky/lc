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
    long long minCost(vector<int> &nums, int x)
    {
        int n = nums.size();
        vector<int> dp(n, 1e9);
        long long rv = 1e12;
        for (auto k = 0; k < n; ++k)     // iteration
        {
            int better = 0;
            for (auto i = 0; i < n; ++i) // all nums
                dp[i] = min(dp[i], nums[(i - k + n) % n]);
            rv = min(rv, accumulate(begin(dp), end(dp), 0ll) + k * x);
        }

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minCost(vector<int>() = {20, 1, 15}, 5);
    cout << r << endl;
}