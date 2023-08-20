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
    int dfs(vector<string> &words, int i, int j, int k)
    {
        if (k >= words.size())
            return 0;

        if (!dp[i][j][k])
        {
            int rv = 0;
            int a = words[k].size() - (words[k].back() - 'a' == i) + dfs(words, words[k][0] - 'a', j, k + 1);
            int b = words[k].size() - (j == words[k][0] - 'a') + dfs(words, i, words[k].back() - 'a', k + 1);
            rv = min(a, b);
            dp[i][j][k] = rv + 1;
        }

        return dp[i][j][k] -1;
    }

    int dp[26][26][1001] = {};

public:
    int minimizeConcatenatedLength(vector<string> &words)
    {
        return words[0].size() + dfs(words, words[0][0] - 'a', words[0].back() - 'a', 1);
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}