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
    int minimumOperations(vector<int> &A)
    {
        vector<int> dp(4, A.size());
        for (int a : A)
        {
            dp[a]--;
            dp[2] = min(dp[2], dp[1]);
            dp[3] = min(dp[3], dp[2]);
        }
        return dp[3];
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minimumOperations(vector<int>() = {3, 3, 2, 2, 1, 1});
    cout << r << endl;

    // r = sol.minimumOperations(vector<int>() = {2, 2, 2, 2, 3, 3});
    // cout << r << endl;

    // r = sol.minimumOperations(vector<int>() = {1, 3, 2, 1, 3, 3});
    // cout << r << endl;

    r = sol.minimumOperations(vector<int>() = {2, 1, 3, 2, 1});
    cout << r << endl;
}