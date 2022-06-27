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
    int dp[7][7][10001] = {};
    vector<vector<int>> valid =
        {
            {1, 2, 3, 4, 5, 6}, // 0
            {2, 3, 4, 5, 6},    // 1
            {1, 3, 5},          // 2
            {1, 2, 4, 5},       // 3
            {1, 3, 5},          // 4
            {1, 2, 3, 4, 6},    // 5
            {1, 5},             // 6
    };

    int dfs(int n, int k = 0, int p1 = 0, int p2 = 0)
    {
        if (k >= n)
            return 1;

        if (!dp[p1][p2][k])
        {
            int rv = 0;
            for (auto &c : valid[p1])
                if (c != p2)
                    rv = (rv + dfs(n, k + 1, c, p1)) % 1000000007;
            dp[p1][p2][k] = rv + 1;
        }
        return dp[p1][p2][k] - 1;
    }

public:
    int distinctSequences(int n)
    {
        return dfs(n);
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.distinctSequences(4);
    cout << r << endl;
}