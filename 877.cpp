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
    int dfs(vector<int> &piles, int i, int j)
    {
        if (i > j)
            return 0;

        if (!dp[i][j])
        {
            int n = piles.size();
            auto l = dfs(piles, i + 1, j);
            auto r = dfs(piles, i, j - 1);
            dp[i][j] = max(piles[i] - l, piles[j] - r);
        }
        return dp[i][j];
    }

    int dp[501][501] = {};

public:
    bool stoneGame(vector<int> &piles)
    {
        return dfs(piles, 0, piles.size() - 1) > 0;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.stoneGame(vector<int>() = {3, 7, 2, 3});
    cout << r << endl;

    r = sol.stoneGame(vector<int>() = {5, 3, 4, 5});
    cout << r << endl;
}