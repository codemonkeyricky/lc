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
    int MOD = 1000000007;
    vector<map<array<int, 3>, int>> dp;
    long long dfs(int n, int k, array<int, 3> cnt)
    {
        array<int,3> empty = {};
        if (k >= n)
            return cnt == empty;

        if (!dp[k].count(cnt))
        {
            long long rv = 0;
            int letters = 0;
            for (auto i = 0; i < 3; ++i)
                if (cnt[i])
                {
                    --cnt[i];
                    rv = (rv + dfs(n, k + 1, cnt)) % MOD;
                    ++cnt[i];
                    ++letters;
                }
            rv = (rv + ((26 - letters) * dfs(n, k + 1, cnt))) % MOD;
            dp[k][cnt] = rv;
        }
        return dp[k][cnt];
    }

public:
    int stringCount(int n)
    {
        array<int, 3> cnt = {1, 2, 1};
        dp = vector<map<array<int, 3>, int>>(n);
        return dfs(n, 0, cnt);
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.stringCount(9);
    cout << r << endl;

    r = sol.stringCount(5);
    cout << r << endl;
}