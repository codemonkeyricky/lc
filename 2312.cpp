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
    long long dp[201][201] = {};
    long long dfs(int m, int n, vector<vector<int>> &prices)
    {
        if (m < 0 || n < 0)
            return 0;

        if(!dp[m][n])
        {
            long long rv = 0;
            for (auto &price : prices)
            {
                auto h = price[0];
                auto w = price[1];
                auto p = price[2];

                if (h <= m && w <= n)
                {
                    auto r0 = p + dfs(m - h, w, prices) + dfs(m, n - w, prices);
                    auto r1 = p + dfs(m - h, n, prices) + dfs(h, n - w, prices);
                    rv = max({rv, r0, r1});
                }
            }

            dp[m][n] = rv + 1;
        }
        return dp[m][n] - 1;
    }

public:
    long long sellingWood(int m, int n, vector<vector<int>> &price)
    {
        for (auto &p : price)
            dp[p[0]][p[1]] = p[2] + 1;
        return dfs(m, n, price);
    }
};

int main()
{
    Solution sol;
    int r;

    // r = sol.sellingWood(4, 6, vector<vector<int>>() = {{3, 2, 10}, {1, 4, 2}, {4, 1, 3}});
    // cout << r << endl;

    r = sol.sellingWood(3, 5, vector<vector<int>>() = {{1, 4, 2}, {2, 2, 7}, {2, 1, 3}});
    cout << r << endl;
}
