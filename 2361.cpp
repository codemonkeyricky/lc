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
    vector<long long> minimumCosts(vector<int> &regular, vector<int> &express, int expressCost)
    {
        int n = regular.size() + 1;
        vector<array<long long, 2>> dp(n);
        dp[0][1] = expressCost;

        for (auto i = 1; i < n; ++i)
        {
            dp[i][0] = min(dp[i - 1][0], dp[i - 1][1]) + regular[i - 1];
            dp[i][1] = min(dp[i - 1][1], dp[i - 1][0] + expressCost) + express[i - 1];
        }

        vector<long long> rv;
        for (auto i = 1; i < n; ++i)
            rv.push_back(min(dp[i][0], dp[i][1]));
        return rv;
    }
};

int main()
{
    Solution sol;
    vector<long long> r;

    r = sol.minimumCosts(vector<int>() = {1, 6, 9, 5}, vector<int>() = {5, 2, 3, 10}, 8);
    for (auto &c : r)
        cout << c << ", ";
    cout << endl;
}