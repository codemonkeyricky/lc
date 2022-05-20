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
    vector<vector<int>> dp; 
    int dfs(vector<array<int, 2>> &rank, int k, int p)
    {
        if (k >= rank.size())
            return 0;

        if (!dp[k][p])
        {

            int r0 = 0, r1 = 0;
            if (!p || rank[p - 1][1] <= rank[k][1])
                r0 += rank[k][1] + dfs(rank, k + 1, k + 1);
            r1 += dfs(rank, k + 1, p);
            dp[k][p] = max(r0, r1) + 1;
        }
        return dp[k][p] - 1;
    }

public:
    int bestTeamScore(vector<int> &scores, vector<int> &ages)
    {
        int n = scores.size();
        dp = vector<vector<int>>(n + 1, vector<int>(n + 2));
        vector<array<int, 2>> sorted;
        for (auto i = 0; i < n; ++i)
            sorted.push_back({ages[i], scores[i]});
        sort(begin(sorted), end(sorted));
        return dfs(sorted, 0, 0);
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.bestTeamScore(vector<int>() = {1, 3, 5, 10, 15}, vector<int>() = {1, 2, 3, 4, 5});
    cout << r << endl;
}