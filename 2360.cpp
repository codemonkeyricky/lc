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
    int longestCycle(vector<int> &e)
    {
        int rv = -1;
        vector<pair<int, int>> dp(e.size(), {-1, -1});
        for (int i = 0; i < e.size(); ++i)
            for (int j = i, dist = 0; j != -1; j = e[j])
            {
                auto [dist_i, from_i] = dp[j];
                if (dist_i == -1)
                    dp[j] = {dist++, i};
                else
                {
                    if (from_i == i)
                        rv = max(rv, dist - dist_i);
                    break;
                }
            }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.longestCycle(vector<int>() = {3, 3, 4, 2, 3});
    cout << r << endl;

    r = sol.longestCycle(vector<int>() = {-1, 4, -1, 2, 0, 4});
    cout << r << endl;
}