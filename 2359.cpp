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
    void dfs(vector<int> &edges, int n, int d, vector<int> &dp)
    {
        /* cycle detection */
        if (dp[n] != -1)
            return;

        dp[n] = d;
        if (edges[n] != -1) 
            dfs(edges, edges[n], d + 1, dp); 
    }

public:
    int closestMeetingNode(vector<int> &edges, int n1, int n2)
    {
        int n = edges.size();

        vector<int> dp1(n, -1), dp2(n, -1);

        dfs(edges, n1, 0, dp1);
        dfs(edges, n2, 0, dp2);

        int sum = 1e9, k = -1;
        for (auto i = 0; i < n; ++i)
            if (dp1[i] != -1 && dp2[i] != -1)
                if (max(dp1[i], dp2[i]) < sum)
                    sum = max(dp1[i], dp2[i]), k = i;
        return k;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.closestMeetingNode(vector<int>() = {4, 4, 8, -1, 9, 8, 4, 4, 1, 1}, 5, 6);
    cout << r << endl;

    r = sol.closestMeetingNode(vector<int>() = {2, 2, 3, -1}, 0, 1);
    cout << r << endl;
}