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
    int dp[256][256] = {};
    int comp[256][256] = {};
    int dfs(vector<vector<int>> &s, vector<vector<int>> &m, int smask, int mmask)
    {
        if (smask == (1 << 8) - 1 && mmask == (1 << 8) - 1)
            return 0;

        int rv = 0, n = s.size();
        if (!dp[smask][mmask])
        {
            for (auto i = 0; i < n; ++i)
                if (!(smask & (1 << i)))
                    for (auto j = 0; j < n; ++j)
                        if (!(mmask & (1 << j)))
                            rv = max(rv, comp[i][j] + dfs(s, m, smask | (1 << i), mmask | (1 << j)));
            dp[smask][mmask] = rv + 1;
        }
        return dp[smask][mmask] - 1;
    }

    void generateComp(vector<vector<int>> &s, vector<vector<int>> &m)
    {
        int n = s.size(), l = s[0].size();
        for (auto i = 0; i < n; ++i)
            for (auto j = 0; j < n; ++j)
                for (auto k = 0; k < l; ++k)
                    comp[i][j] += s[i][k] == m[j][k];
    }

public:
    int maxCompatibilitySum(vector<vector<int>> &students, vector<vector<int>> &mentors)
    {
        generateComp(students, mentors);
        return dfs(students, mentors, 0, 0);
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.maxCompatibilitySum(vector<vector<int>>() = {{1, 1, 0}, {1, 0, 1}, {0, 0, 1}},
                                vector<vector<int>>() = {{1, 0, 0}, {0, 0, 1}, {1, 1, 0}});
    cout << r << endl;
}