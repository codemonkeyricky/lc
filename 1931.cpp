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
    int dfs(int n, int mask, int k)
    {
        if (k >= n - 1)
            return 1;

        if (!dp[mask][k])
        {
            int rv = 0;
            for (auto &m : map[mask])
                rv = (rv + dfs(n, m, k + 1)) % 1000000007;
            dp[mask][k] = rv + 1; 
        }
        return dp[mask][k] - 1;
    }

    void generate(int m, int mask, int prev, int k)
    {
        if (k >= m)
        {
            possible.push_back(mask);
            return;
        }

        for (auto i = 0; i < 3; ++i)
            if (i != prev)
                generate(m, mask | (i << (k * 2)), i, k + 1);
    }

    vector<int> possible;
    unordered_map<int, vector<int>> map;
    vector<vector<int>> dp;

public:
    int colorTheGrid(int m, int n)
    {
        generate(m, 0, -1, 0);

        for (auto &i : possible)
            for (auto &j : possible)
            {
                bool valid = true;
                auto d = i ^ j;
                for (int k = 0; k < m && valid; ++k, d >>= 2)
                    if ((d & 0x3) == 0)
                        valid = false;

                if (valid)
                    map[i].push_back(j);
            }

        dp = vector<vector<int>>(1025, vector<int>(1025));
        int rv = 0;
        for (auto & m : map)
            rv = (rv + dfs(n, m.first, 0)) % 1000000007;
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.colorTheGrid(2, 2);
    cout << r << endl;
}