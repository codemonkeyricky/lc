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

int dp[1001] = {};
class Solution
{
public:
    bool divisorGame(int n)
    {
        if (n == 1)
            return false;

        if (dp[n])
            return dp[n] - 1;

        for (auto i = 1; i * i <= n; ++i)
            if (n % i == 0)
                if (!divisorGame(n - i))
                {
                    dp[n] = 1 + 1;
                    return dp[n] - 1;
                }
        dp[n] = 1;
        return dp[n] - 1;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.divisorGame(2);
    cout << r << endl;

    r = sol.divisorGame(9);
    cout << r << endl;

    r = sol.divisorGame(7);
    cout << r << endl;

    r = sol.divisorGame(2);
    cout << r << endl;
}