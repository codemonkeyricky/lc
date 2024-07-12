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
    int dfs(string &word, char p, int k)
    {
        if (k == word.size())
            return 0;

        if (!dp[k][p - 'a'])
        {
            int rv = 1e9;
            for (auto i = 'a'; i <= 'z'; ++i)
                if (abs(p - i) > 1)
                    rv = min(rv, (i != word[k]) + dfs(word, i, k + 1));
            dp[k][p - 'a'] = rv + 1;
        }
        return dp[k][p - 'a'] - 1;
    }

    vector<array<int, 28>> dp;

public:
    int removeAlmostEqualCharacters(string word)
    {
        dp = vector<array<int, 28>>(word.size());
        return dfs(word, 'z' + 2, 0);
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.removeAlmostEqualCharacters("zyxyxyz");
    cout << r << endl;

    r = sol.removeAlmostEqualCharacters("aa");
    cout << r << endl;

    r = sol.removeAlmostEqualCharacters("aaaaa");
    cout << r << endl;
}