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

int dp[5001][4][65][65] = {};
class Solution
{
    int dfs(int n, int i = 0, int j = 0, int curr = 0, int prev = 0)
    {
        if (i >= n)
            return 1;

        if (j >= 3)
            return dfs(n, i + 1, 0, 0, curr);

        int ni = n - i;
        int nj = 3 - j;

        if (!dp[ni][nj][curr][prev])
        {
            int rv = 0;
            for (auto k = 1; k <= 3; ++k)
            {
                int up = (prev & (0x3 << (j * 2))) >> (j * 2);
                int left = j ? ((curr & (0x3 << ((j - 1) * 2))) >> (j - 1) * 2) : 0;
                if (k != up && k != left)
                    rv = (rv + dfs(n, i, j + 1, curr | (k << (j * 2)), prev)) % 1000000007;
            }
            dp[ni][nj][curr][prev] = rv + 1;
        }
        return dp[ni][nj][curr][prev] - 1;
    }

public:
    int numOfWays(int n)
    {
        return dfs(n);
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.numOfWays(5000);
    cout << r << endl;

    r = sol.numOfWays(1);
    cout << r << endl;
}
