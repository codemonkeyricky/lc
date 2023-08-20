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

int dp[51][51][51][2] = {};
class Solution
{
    int dfs(int x, int y, int z, int k)
    {
        if (x == 0 && y == 0 && z == 0)
            return 0;

        if (!dp[x][y][z][k])
        {
            int a = 0, b = 0, c = 0;
            if (x && k == 1) // prev ends in A
                a = 2 + dfs(x - 1, y, z, 0);
            if (y && k == 0) // prev ends in B
                b = 2 + dfs(x, y - 1, z, 1);
            if (z && k == 1) // prev ends in A
                c = 2 + dfs(x, y, z - 1, 1);
            dp[x][y][z][k] = max({a, b, c}) + 1;
        }
        return dp[x][y][z][k] - 1;
    }

public:
    int longestString(int x, int y, int z)
    {
        int a = 0, b = 0, c = 0;
        if (x)
            a = 2 + dfs(x - 1, y, z, 0);
        if (y)
            b = 2 + dfs(x, y - 1, z, 1);
        if (z)
            c = 2 + dfs(x, y, z - 1, 1);
        return max({a, b, c});
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.longestString(3, 1, 21);
    cout << r << endl;

    r = sol.longestString(2, 5, 1);
    cout << r << endl;
}