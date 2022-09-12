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
    int dp[2][11][2048] = {};

    int dfs(int n, int d, int l = 1, int mask = 0)
    {
        if (d == 0)
            return mask ? 1 : 0;

        if (!dp[l][d][mask])
        {
            auto dd = d - 1;
            int p = 1;
            while (dd)
                p *= 10, --dd;

            auto digit = (n / p) % 10;

            int rv = 0;
            for (int i = l ? digit : 9; i >= 0; --i)
                if (!((1 << i) & mask))
                {
                    auto mmask = 0;
                    if (mask || i)
                        mmask = (1 << i) | mask;
                    rv += dfs(n, d - 1, l && i == digit, mmask);
                }
            dp[l][d][mask] = rv + 1;
        }
        return dp[l][d][mask] - 1;
    }

public:
    int countSpecialNumbers(int n)
    {
        int d = 0;
        auto nn = n;
        while (nn)
            ++d, nn /= 10;
        return dfs(n, d);
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.countSpecialNumbers(100);
    cout << r << endl;

    r = sol.countSpecialNumbers(20);
    cout << r << endl;
}