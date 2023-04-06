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
    int numRollsToTarget(int n, int k, int target)
    {
        int dp[31][1001] = {};
        dp[0][0] = 1;
        for (auto i = 1; i < n + 1; ++i)
            for (auto face = 1; face <= k; ++face)
                for (auto s = 1; s <= target; ++s)
                    if (s - face >= 0)
                        dp[i][s] = (dp[i][s] + dp[i - 1][s - face]) % 1000000007;

        return dp[n][target];
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.numRollsToTarget(30, 30, 500);
    cout << r << endl;

    r = sol.numRollsToTarget(2, 6, 7);
    cout << r << endl;
}