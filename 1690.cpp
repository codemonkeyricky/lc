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
    int getRange(int i, int j)
    {
        return sum[j + 1] - sum[i];
    }

    int dfs(vector<int> &stones, int i, int j)
    {
        int n = stones.size();

        if (i > j)
            return 0;

        if (!dp[i][j])
        {
            int sum = getRange(i, j);
            auto a = sum - stones[i] - dfs(stones, i + 1, j);
            auto b = sum - stones[j] - dfs(stones, i, j - 1);
            dp[i][j] = max(a, b) + 1;
        }
        return dp[i][j] - 1;
    }

    vector<int> sum;
    int dp[1001][1001] = {};

public:
    int stoneGameVII(vector<int> &stones)
    {
        int n = stones.size();
        sum = vector<int>(n + 1);
        for (auto i = 1; i < n + 1; ++i)
            sum[i] = sum[i - 1] + stones[i - 1];
        return dfs(stones, 0, stones.size() - 1);
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.stoneGameVII(vector<int>() = {5, 3, 1, 4, 2});
    cout << r << endl;
}