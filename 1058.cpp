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
#include <sstream>

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
    double dfs(vector<double> &prices, int k, int target)
    {
        int n = prices.size();

        if (k >= n)
            if (target == 0)
                return 0;
            else
                return 1e9;

        if (target < 0)
            return 1e9;

        if (!dp[k][target])
        {
            auto ce = 1 - prices[k];
            auto fe = prices[k];
            double r0 = 1e9, r1 = 1e9;
            r0 = fe + dfs(prices, k + 1, target);
            r1 = ce + dfs(prices, k + 1, target - 1);
            dp[k][target] = min(r0, r1) + 1;
        }
        return dp[k][target] - 1;
    }

    vector<vector<double>> dp;

public:
    string minimizeError(vector<string> &prices, int target)
    {
        vector<double> pp;
        for (auto &p : prices)
        {
            auto f = stof(p);
            target -= floor(f);
            if (ceil(f) != floor(f))
                pp.push_back(f - floor(f));
        }

        if (target < 0)
            return "-1";

        dp = vector<vector<double>>(pp.size(), vector<double>(target + 1));
        auto rv = dfs(pp, 0, target);
        if (rv >= 1e9)
            return "-1";

        ostringstream out;
        out.precision(3);
        out << std::fixed << rv; 
        return out.str();
    }
};

int main()
{
    Solution sol;
    string r;

    r = sol.minimizeError(vector<string>() = {"2.146", "2.656", "2.908", "2.739", "2.589"}, 11);
    cout << r << endl;

    r = sol.minimizeError(vector<string>() = {"20.500","20.500","20.500","20.500","20.500","20.500","20.500","20.500","20.500","20.500","20.500","20.500","20.500","20.500","20.500","20.500","20.500","20.500","20.500","20.500","20.500","20.500","20.500","20.500","20.500","20.500","20.500","20.500","20.500","20.500","20.500","20.500","20.500","20.500","20.500","20.500","20.500","20.500","20.500","20.500","20.500","20.500","20.500","20.500","20.500","20.500","20.500","20.500","20.500","20.500"}, 1025);
    cout << r << endl;

    // r = sol.minimizeError(vector<string>() = {"20.500", "20.500", "20.500", "20.500", "20.500", "20.500", "20.500", "20.500", "20.500", "20.500", "20.500", "20.500", "20.500", "20.500", "20.500", "20.500", "20.500", "20.500", "20.500", "20.500", "20.500", "20.500", "20.500", "20.500", "20.500", "20.500", "20.500", "20.500", "20.500", "20.500", "20.500", "20.500", "20.500", "20.500", "20.500", "20.500", "20.500", "20.500", "20.500", "20.500", "20.500", "20.500", "20.500", "20.500", "20.500", "20.500", "20.500", "20.500", "20.500", "20.500"}, 999);
    // cout << r << endl;

    // r = sol.minimizeError(vector<string>() = {"20.000", "20.000", "20.000", "20.000", "20.000", "20.000", "20.000", "20.000", "20.000", "20.000", "20.000", "20.000", "20.000", "20.000", "20.000", "20.000", "20.000", "20.000", "20.000", "20.000", "20.000", "20.000", "20.000", "20.000", "20.000", "20.000", "20.000", "20.000", "20.000", "20.000", "20.000", "20.000", "20.000", "20.000", "20.000", "20.000", "20.000", "20.000", "20.000", "20.000", "20.000", "20.000", "20.000", "20.000", "20.000", "20.000", "20.000", "20.000", "20.000", "20.000"}, 999);
    // cout << r << endl;

    r = sol.minimizeError(vector<string>() = {"1.500", "2.500", "3.500"}, 6);
    cout << r << endl;

    r = sol.minimizeError(vector<string>() = {"0.700", "2.800", "4.900"}, 8);
    cout << r << endl;
}