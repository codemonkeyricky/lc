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
    int dfs(TreeNode *curr, bool result)
    {
        if (!curr)
            return -1;

        if (curr->val == 1 || curr->val == 0)
            return curr->val != result;

        auto lt = dfs(curr->left, true);
        auto lf = dfs(curr->left, false);
        auto rt = dfs(curr->right, true);
        auto rf = dfs(curr->right, false);
        if (curr->val == 2)
        {
            // OR
            if (result)
                return min(lt + min(rt, rf), min(lt, lf) + rt);
            else
                return lf + rf;
        }
        else if (curr->val == 3)
        {
            // AND
            if (result)
                return lt + rt;
            else
                return min(lf + min(rt, rf), min(lt, lf) + rf);
        }
        else if (curr->val == 4)
        {
            // XOR
            if (result)
                return min(lt + rf, lf + rt);
            else 
                return min(lf + rf, lt + rt);
        }
        else // 5 
        {
            // NOT
            if (curr->left)
                if (result)
                    return lf;
                else 
                    return lt;
            else 
                if (result)
                    return rf;
                else
                    return rt;
        }
    }

public:
    int minimumFlips(TreeNode *root, bool result)
    {
        return dfs(root, result);
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}