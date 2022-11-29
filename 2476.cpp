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
    void dfs(TreeNode *curr, vector<int> &arr)
    {
        if (curr)
        {
            dfs(curr->left, arr);
            arr.push_back(curr->val);
            dfs(curr->right, arr);
        }
    }

public:
    vector<vector<int>> closestNodes(TreeNode *root, vector<int> &queries)
    {
        vector<vector<int>> rv;
        vector<int> arr;
        dfs(root, arr);
        for (auto &q : queries)
        {
            int mmin, mmax;
            auto it = upper_bound(begin(arr), end(arr), q);
            mmin = it != begin(arr) ? *prev(it) : -1;

            it = lower_bound(begin(arr), end(arr), q);
            mmax = it != end(arr) ? *it : -1;

            rv.push_back({mmin, mmax});
        }

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}