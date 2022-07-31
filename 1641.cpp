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
    int countVowelStrings(int n)
    {
        int dp[51][5] = {};
        for (auto i = 0; i < 5; ++i)
            dp[0][i] = 1;

        for (auto i = 1; i < n; ++i)
            for (auto j = 0; j < 5; ++j)
                dp[i][j] += dp[i - 1][j] + (j ? dp[i][j - 1] : 0);

        int rv = 0;
        for (auto i = 0; i < 5; ++i)
            rv += dp[n - 1][i];

        return rv; 
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.countVowelStrings(2);
    cout << r << endl;
}