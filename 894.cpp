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

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution
{
    // global map
    unordered_map<int, vector<TreeNode *>> dp;

public:
    // recursion is very lengthy: memorization can help a little bit
    vector<TreeNode *> allPossibleFBT(int n)
    {
        vector<TreeNode *> rv;
        if (n < 1 || n % 2 == 0)
            return rv;

        if (dp.count(n))
            return dp[n];

        if (n == 1)
        {
            rv.push_back(new TreeNode());
            dp[1] = rv;
            return rv;
        }

        for (int i = 1; i < n; i += 2)
        {
            vector<TreeNode *> l = allPossibleFBT(i);
            vector<TreeNode *> r = allPossibleFBT(n - 1 - i);

            for (int j = 0; j < l.size(); j++)
                for (int k = 0; k < r.size(); k++)
                {
                    TreeNode *root = new TreeNode();
                    root->left = l[j], root->right = r[k],
                    rv.push_back(root);
                }
        }

        dp[n] = rv; 

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    sol.allPossibleFBT(13);
    cout << r << endl;
}