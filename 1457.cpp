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
    int dfs(TreeNode *curr, array<int, 10> &nums)
    {
        ++nums[curr->val];
        if (!curr->left && !curr->right)
        {
            int odd = 0;
            for (auto &n : nums)
                if (n % 2)
                    ++odd;
            --nums[curr->val];
            return odd <= 1;
        }

        int rv = 0;
        if (curr->left)
            rv += dfs(curr->left, nums);
        if (curr->right)
            rv += dfs(curr->right, nums);

        --nums[curr->val];

        return rv; 
    }

public:
    int pseudoPalindromicPaths(TreeNode *root)
    {
        return dfs(root, array<int, 10>() = {});
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}