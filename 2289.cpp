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
    int totalSteps(vector<int> &A)
    {
        int n = A.size(), res = 0;
        vector<int> stack, dp(n);
        for (int i = n - 1; i >= 0; --i)
        {
            while (!stack.empty() && A[i] > A[stack.back()])
            {
                dp[i] = max(++dp[i], dp[stack.back()]);
                stack.pop_back();
                res = max(res, dp[i]);
            }
            stack.push_back(i);
        }
        return res;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.totalSteps(vector<int>() = {10, 1, 2, 3, 4, 5, 6, 1, 2, 3});
    cout << r << endl;

    r = sol.totalSteps(vector<int>() = {5, 3, 4, 4, 7, 3, 6, 11, 8, 5, 11});
    cout << r << endl;
}