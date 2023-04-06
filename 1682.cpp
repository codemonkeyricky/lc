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
    int dp[252][252][27] = {};
    int dfs(string &s, int i, int j, int k)
    {
        if (i >= j)
            return 0;

        if (!dp[i][j][k])
        {
            int r0 = 0, r1 = 0, r2 = 0;
            if (s[i] == s[j])
                if (k == 26 || s[i] != k + 'a')
                    r0 = 2 + dfs(s, i + 1, j - 1, s[i] - 'a');
            r1 = dfs(s, i + 1, j, k);
            r2 = dfs(s, i, j - 1, k);
            dp[i][j][k] = max({r0, r1, r2}) + 1;
        }
        return dp[i][j][k] - 1;
    }

public:
    int longestPalindromeSubseq(string s)
    {
        return dfs(s, 0, s.size() - 1, 26); 
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.longestPalindromeSubseq("lszahrldcdlsssyyvgr");
    cout << r << endl;
}