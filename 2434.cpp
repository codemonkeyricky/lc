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
    string robotWithString(string s)
    {
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(26, -1));
        for (int i = n - 1; i >= 0; --i)
        {
            if (i < n - 1)
                dp[i] = dp[i + 1];
            dp[i][s[i] - 'a'] = i;
        }

        string rv, t;
        for (auto i = 0; i < n;)
        {
            int j;
            for (j = 0; j < 26; ++j)
                if (dp[i][j] != -1 && dp[i][j] >= i)
                    break;
            while (t.size() && j < 26 && t.back() <= j + 'a')
                rv += t.back(), t.pop_back();

            while (i < dp[i][j])
                t.push_back(s[i++]);

            rv.push_back(s[i++]);
        }

        while (t.size())
            rv += t.back(), t.pop_back();

        return rv;
    }
};

int main()
{
    Solution sol;
    string r;

    r = sol.robotWithString("vzhofnpo");
    cout << r << endl;

    r = sol.robotWithString("bac");
    cout << r << endl;

    r = sol.robotWithString("bdda");
    cout << r << endl;
}