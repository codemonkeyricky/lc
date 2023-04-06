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
    int countRoutes(vector<int> &loc, int start, int finish, int fuel)
    {
        int n = loc.size();

        int dp[201][101] = {};

        // base case
        dp[0][start] = 1;

        for (auto f = 0; f <= fuel; ++f)
            for (auto i = 0; i < n; ++i)
                for (auto j = 0; j < n; ++j)
                    if (i != j)
                        if (f - abs(loc[i] - loc[j]) >= 0)
                            dp[f][i] = (dp[f][i] + dp[f - abs(loc[i] - loc[j])][j]) % 1000000007;

        long rv = 0;
        for (auto i = 0; i < 201; ++i)
            rv = (rv + dp[i][finish]) % 1000000007;
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.countRoutes(vector<int>() = {2, 3, 6, 8, 4}, 1, 3, 5);
    cout << r << endl;
}