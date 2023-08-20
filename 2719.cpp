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
    int dfs(string &num, int k, int ceil, int curr, int min_sum, int max_sum, vector<vector<array<int, 2>>> &dp)
    {
        if (curr > max_sum)
            return 0;
        
        if (k >= num.size())
            return curr >= min_sum;

        if (!dp[k][curr][ceil])
        {
            long rv = 0;
            for (auto i = ceil ? (num[k] - '0') : 9; i >= 0; --i)
                rv = (rv + dfs(num, k + 1,
                               ceil && (i + '0' == num[k]),
                               curr + i,
                               min_sum, max_sum, dp)) %
                     1000000007;
            dp[k][curr][ceil] = rv + 1;
        }
        return dp[k][curr][ceil] - 1;
    }

    int cnt(string &num, int min_sum, int max_sum)
    {
        vector<vector<array<int, 2>>> dp = vector<vector<array<int, 2>>>(num.size(), vector<array<int, 2>>(max_sum + 1));
        return dfs(num, 0, 1, 0, min_sum, max_sum, dp);
    }

    bool isGood(string &n, int mmin, int mmax)
    {
        int sum = 0;
        for (auto &c : n)
            sum += c - '0';
        return mmin <= sum && sum <= mmax;
    }

public:
    int count(string num1, string num2, int min_sum, int max_sum)
    {
        auto a = cnt(num2, min_sum, max_sum);
        auto b = cnt(num1, min_sum, max_sum);
        return a - b + isGood(num1, min_sum, max_sum);
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.count("862662375825717340797", "1341489267173864014004", 204, 338);
    cout << r << endl;

    r = sol.count("1", "20", 2, 10);
    cout << r << endl;

    r = sol.count("1", "19", 2, 10);
    cout << r << endl;

    r = sol.count("1", "12", 1, 8);
    cout << r << endl;
}