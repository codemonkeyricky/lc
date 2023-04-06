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
#include <climits>

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
    int dp[1000] = {}, last[1000] = {};
    int dfs(vector<int> &n, vector<vector<int>> &al, int i, int p, int &ids)
    {
        int res = n[i];
        for (auto j : al[i])
        {
            if (j != p)
            {
                int id = ids++;
                dp[id] = dfs(n, al, j, i, ids);
                last[id] = ids;
                res ^= dp[id];
            }
        }
        return res;
    }

public:
    int minimumScore(vector<int> &n, vector<vector<int>> &edges)
    {
        int ids = 0, res = INT_MAX;
        vector<vector<int>> al(n.size());
        for (auto &e : edges)
            al[e[0]].push_back(e[1]), al[e[1]].push_back(e[0]);

        int all = dfs(n, al, 0, -1, ids);
        for (int i = 0; i < edges.size(); ++i)
        {
            for (int j = i + 1; j < edges.size(); ++j)
            {
                int p1 = j < last[i] ? all ^ dp[i] : all ^ dp[i] ^ dp[j];
                int p2 = j < last[i] ? dp[i] ^ dp[j] : dp[i];
                res = min(res, max({p1, p2, dp[j]}) - min({p1, p2, dp[j]}));
            }
        }
        return res;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minimumScore(vector<int>() = {1, 5, 5, 4, 11}, vector<vector<int>>() = {{0, 1}, {1, 2}, {1, 3}, {3, 4}});
    cout << r << endl;
}