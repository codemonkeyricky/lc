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
    vector<int> minDifference(vector<int> &nums, vector<vector<int>> &queries)
    {
        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(101));
        for (auto i = 0; i < n; ++i)
        {
            dp[i] = i ? dp[i - 1] : dp[i];
            ++dp[i][nums[i]];
        }

        vector<int> rv;
        vector<int> diff(101);
        for (auto &q : queries)
        {
            int i = q[0], j = q[1];
            for (auto k = 0; k <= 100; ++k)
                diff[k] = dp[j][k] - (i ? dp[i - 1][k] : 0);

            int last = -1, r = 101;
            for (auto k = 0; k <= 100; ++k)
                if (diff[k])
                {
                    if (last != -1)
                        r = min(r, k - last);
                    last = k;
                }

            rv.push_back(r == 101 ? -1 : r);
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    sol.minDifference(vector<int>() = {1, 3, 4, 8}, vector<vector<int>>() = {{0, 1}, {1, 2}, {2, 3}, {0, 3}});
}