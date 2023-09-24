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
    int maximizeTheProfit(int n, vector<vector<int>> &offers)
    {
        sort(begin(offers), end(offers), [](vector<int> &l, vector<int> &r)
             { return l[1] < r[1]; });
        vector<int> dp(n);
        for (auto i = 0, j = 0; j < n; ++j)
        {
            dp[j] = j ? dp[j - 1] : 0;
            while (i < offers.size() && offers[i][1] == j)
            {
                dp[j] = max(dp[j], offers[i][2] + (offers[i][0] ? dp[offers[i][0] - 1] : 0));
                ++i;
            }
        }

        return dp[n - 1];
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.maximizeTheProfit(4, vector<vector<int>>() = {{0, 0, 5}, {3, 3, 1}, {1, 2, 5}, {0, 0, 7}});
    cout << r << endl;

    r = sol.maximizeTheProfit(5, vector<vector<int>>() = {{0, 0, 1}, {0, 2, 2}, {1, 3, 2}});
    cout << r << endl;
}