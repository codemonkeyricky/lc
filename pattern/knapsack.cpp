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

class Knapsack
{
public:
    // Tops down
    int topsdown(vector<int> &weights, vector<int> &vals, int k, int w)
    {
        if (k >= vals.size())
            return 0;

        if (weights[k] > w)
            return topsdown(weights, vals, k + 1, w);

        int a = vals[k] + topsdown(weights, vals, k + 1, w - weights[k]);
        int b = topsdown(weights, vals, k + 1, w);
        return max(a, b);
    }

    // Bottoms up
    int bottomsup(vector<int> &weights, vector<int> &vals, int k, int w)
    {
        int n = weights.size();
        vector<vector<int>> dp(n + 1, vector<int>(w + 1));

        // Introduce one new item every iteration
        for (auto i = 1; i <= n; ++i)
            // Iterate all possible weight for this item
            for (auto ww = 0; ww <= w; ++ww)
            {
                // Results carry from previous set of items
                dp[i][ww] = dp[i - 1][ww];

                // Consider including current item only if bag fits
                if (ww >= weights[i - 1])
                    dp[i][ww] = max(dp[i][ww], vals[i - 1] + dp[i - 1][ww - weights[i - 1]]);
            }

        return dp[n][w];
    }

    // Space optimized
    int bottomsup_opt(vector<int> &weights, vector<int> &vals, int k, int w)
    {
        int n = weights.size();
        vector<int> dp(w + 1);

        for (auto i = 1; i <= n; ++i)
            for (int ww = w; ww >= 0; --ww)
                if (ww >= weights[i - 1])
                    dp[ww] = max(dp[ww], vals[i - 1] + dp[ww - weights[i - 1]]);

        return dp[w];
    }
};

int main()
{
    Knapsack knapsack;
    int r;

    vector<int> p = {10, 15, 40};
    vector<int> w = {1, 2, 3};

    r = knapsack.bottomsup_opt(w, p, 0, 50);
    cout << r << endl;

    r = knapsack.bottomsup(w, p, 0, 50);
    cout << r << endl;

    r = knapsack.topsdown(w, p, 0, 50);
    cout << r << endl;
}