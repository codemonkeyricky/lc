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
    int dp[50][50] = {};
    int minScoreTriangulation(vector<int> &A, int i = 0, int j = 0, int res = 0)
    {
        if (j == 0)
            j = A.size() - 1;
        if (dp[i][j] != 0)
            return dp[i][j];
        for (auto k = i + 1; k < j; ++k)
        {
            res = min(res == 0 ? INT_MAX : res,
                      minScoreTriangulation(A, i, k) + A[i] * A[k] * A[j] + minScoreTriangulation(A, k, j));
        }
        return dp[i][j] = res;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minScoreTriangulation(vector<int>() = {2, 2, 2, 2, 1});
    cout << r << endl;

    r = sol.minScoreTriangulation(vector<int>() = {4, 3, 4, 3, 5});
    cout << r << endl;

    r = sol.minScoreTriangulation(vector<int>() = {1, 3, 1, 4, 1, 5});
    cout << r << endl;

    r = sol.minScoreTriangulation(vector<int>() = {1, 2, 3});
    cout << r << endl;

    r = sol.minScoreTriangulation(vector<int>() = {3, 7, 4, 5});
    cout << r << endl;
}