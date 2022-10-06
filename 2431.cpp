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
    int maxTastiness(vector<int> &price, vector<int> &tasty, int maxAmount, int maxCoupons)
    {
        int n = price.size();
        vector<vector<int>> dp(maxCoupons + 1, vector<int>(maxAmount + 1));

        for (int i = 0; i < n; i++)
        {
            for (int coupon = maxCoupons; coupon >= 0; coupon--)
            {
                for (int amount = maxAmount; amount >= 1; amount--)
                {
                    if (coupon && (amount - price[i] / 2) >= 0)
                        dp[coupon][amount] = max(dp[coupon][amount], tasty[i] + dp[coupon - 1][amount - price[i] / 2]);

                    if (amount - price[i] >= 0)
                        dp[coupon][amount] = max(dp[coupon][amount], tasty[i] + dp[coupon][amount - price[i]]);
                }
            }
        }
        return dp[maxCoupons][maxAmount];
    }
};

int main()
{
    Solution sol;
    int r;

    // r = sol.maxTastiness(vector<int>() = {136, 101, 275, 590, 200, 331, 600, 809, 165, 276, 515, 615, 584, 337, 63}, vector<int>() = {463, 846, 856, 733, 839, 60, 223, 167, 575, 409, 852, 8, 250, 537, 797}, 899, 5);
    // cout << r << endl;

    // r = sol.maxTastiness(vector<int>() = {136, 331, 600, 275, 809, 101, 165, 276, 590, 200, 515, 615, 584, 337, 63}, vector<int>() = {463, 60, 223, 856, 167, 846, 575, 409, 733, 839, 852, 8, 250, 537, 797}, 899, 5);
    // cout << r << endl;

    // r = sol.maxTastiness(vector<int>() = {10, 15, 7}, vector<int>() = {5, 8, 20}, 10, 2);
    // cout << r << endl;

    r = sol.maxTastiness(vector<int>() = {10, 20, 20}, vector<int>() = {5, 8, 8}, 20, 1);
    cout << r << endl;
}