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

// class Solution
// {
//     vector<string> dp;
//     string dfs(vector<int> &costs, int money)
//     {
//         if (money == 0)
//             return "";

//         if (dp[money].empty())
//         {
//             string rv;
//             for (auto i = 0; i < costs.size(); ++i)
//             {
//                 if (money >= costs[i])
//                 {
//                     auto r1 = string(1, '1' + i);
//                     auto r2 = dfs(costs, money - costs[i]);
//                     auto r = r1 + r2;
//                     if (r2 != "na" && (r.size() > rv.size() || (r.size() == rv.size() && r > rv)))
//                         rv = r;
//                 }
//             }
//             dp[money] = rv == "" ? "na" : rv;
//         }
//         return dp[money];
//     }

// public:
//     string largestNumber(vector<int> &cost, int target)
//     {
//         dp = vector<string>(5001);
//         auto r =  dfs(cost, target);
//         return r == "na" ? "0" : r;
//     }
// };

class Solution
{
public:
    string largestNumber(vector<int> &cost, int target)
    {
        vector<string> dp(5001, "0");
        dp[0] = "";
        for(auto k = 0; k <= target; ++k)
            for (auto i = 0; i < 9; ++i)
                if (k - cost[i] >= 0 && dp[k - cost[i]] != "0")
                {
                    auto a = to_string(i + 1) + dp[k - cost[i]];
                    if (dp[k] == "0" || (a.size() > dp[k].size() || (a.size() == dp[k].size() && a > dp[k])))
                        dp[k] = a;
                }
        return dp[target];
    }
};


int main()
{
    Solution sol;
    string r;

    r = sol.largestNumber(vector<int>() = {4, 3, 2, 5, 6, 7, 2, 5, 5}, 9);
    cout << r << endl;
}