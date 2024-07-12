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
    inline bool isPart(int u, int set)
    {
        return (1 << u) & set;
    }

public:
    int numberOfSets(int n, int maxDistance, vector<vector<int>> &roads)
    {
        vector<vector<int>> al(n, vector<int>(n, 1e9));
        for (auto &r : roads)
        {
            auto u = r[0], v = r[1], w = r[2];
            al[u][v] = al[v][u] = min(w, al[u][v]);
        }

        int rv = 0;
        for (auto set = 0; set < (1 << n); ++set)
        {
            vector<vector<int>> dp(n, vector<int>(n));
            for (auto u = 0; u < n; ++u)
                for (auto v = 0; v < n; ++v)
                    if (u != v)
                        if (isPart(u, set) && isPart(v, set))
                            dp[u][v] = dp[v][u] = al[u][v];

            for (auto k = 0; k < n; ++k)
                if (isPart(k, set))
                    for (auto i = 0; i < n; ++i)
                        if (isPart(i, set))
                            for (auto j = 0; j < n; ++j)
                                if (isPart(j, set))
                                    if (dp[i][j] > dp[i][k] + dp[k][j])
                                        dp[i][j] = dp[i][k] + dp[k][j];

            bool valid = true;
            for (auto u = 0; u < n && valid; ++u)
                for (auto v = 0; v < n && valid; ++v)
                    if (u != v)
                        if (isPart(u, set) && isPart(v, set))
                            if (dp[u][v] > maxDistance)
                                valid = false;
        
            rv += valid;
        }

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.numberOfSets(1, 10, vector<vector<int>>() = {});
    cout << r << endl;

    r = sol.numberOfSets(3, 5, vector<vector<int>>() = {{0, 1, 20}, {0, 1, 10}, {1, 2, 2}, {0, 2, 2}});
    cout << r << endl;

    r = sol.numberOfSets(3, 5, vector<vector<int>>() = {{0, 1, 2}, {1, 2, 10}, {0, 2, 10}});
    cout << r << endl;
}