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
    vector<int> dp;
    int dfs(string &keys, int k)
    {
        int cnt = (keys[k] == '7' || keys[k] == '9') ? 4 : 3;
        int n = keys.size();
        int rv = 0;
        if (k >= n)
            return 1;

        if (!dp[k])
        {
            for (auto i = k; i < n && i < k + cnt && ((i == k) || keys[i - 1] == keys[i]); ++i)
                rv = (rv + dfs(keys, i + 1)) % 1000000007;
            dp[k] = rv + 1;
        }
        return dp[k] - 1;
    }

public:
    int countTexts(string keys)
    {
        dp = vector<int>(keys.size());
        return dfs(keys, 0);
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.countTexts("22233");
    cout << r << endl;
}