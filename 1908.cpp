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
    map<vector<int>, bool> dp;

    bool dfs(vector<int> piles)
    {
        if (accumulate(begin(piles), end(piles), 0) == 0)
            return false;

        sort(begin(piles), end(piles));
        if (!dp.count(piles))
        {
            bool rv = false;
            for (auto i = 0; i < piles.size() && !rv; ++i)
            {
                for (auto j = 1; j <= piles[i]; ++j)
                {
                    piles[i] -= j;
                    if (!dfs(piles))
                    {
                        piles[i] += j;
                        rv = true;
                        break; 
                    }
                    piles[i] += j;
                }
            }

            dp[piles] = rv;
        }
        return dp[piles];
    }

public:
    bool nimGame(vector<int> &piles)
    {
        return dfs(piles);
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.nimGame(vector<int>() = {1, 1});
    cout << r << endl;

    r = sol.nimGame(vector<int>() = {7, 6, 6, 7});
    cout << r << endl;
}