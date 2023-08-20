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
    string dec(string &s)
    {
        int borrow = true;
        for(int i = s.size()-1; i >= 0 && borrow; --i)
        {
            borrow = false;
            if (s[i] == '0')
                s[i] = '9', borrow = true;
            else
                --s[i];
        }
        if (s[0] == '0')
            return s.substr(1);
        return s;
    }

    long dfs(string &s, int p, int k, bool ceil)
    {
        if (k >= s.size())
            return 1;

        if (!dp[p][k][ceil])
        {
            long rv = 0;
            for (int i = ceil ? s[k] - '0' : 9; i >= 0; --i)
                if (p == 10 || (i == p + 1 || i == p - 1))
                    rv = (rv + dfs(s,
                                   (p == 10 && i == 0) ? 10 : i,
                                   k + 1,
                                   ceil && i == s[k] - '0')) %
                         1000000007;
            dp[p][k][ceil] = rv + 1;
        }
        return dp[p][k][ceil] - 1;
    }

    vector<vector<vector<long>>> dp;

public:
    int countSteppingNumbers(string low, string high)
    {
        dp = vector<vector<vector<long>>>(11, vector<vector<long>>(high.size(), vector<long>(2)));
        auto a = dfs(high, 10, 0, true);
        string low_dec = dec(low);
        dp = vector<vector<vector<long>>>(11, vector<vector<long>>(low_dec.size(), vector<long>(2)));
        auto b = dfs(low_dec, 10, 0, true);
        auto rv = a -b;
        while (rv < 0)
            rv += 1000000007;
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    // r = sol.countSteppingNumbers("90", "101");
    // cout << r << endl;

    r = sol.countSteppingNumbers("1", "11");
    cout << r << endl;
}