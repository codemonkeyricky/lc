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
    void dfs(vector<vector<int>> &al, TreeNode *curr, TreeNode *p = nullptr)
    {
        if (p)
            al[curr->val].push_back(p->val);
        if (curr->left)
            al[curr->val].push_back(curr->left->val), dfs(al, curr->left, curr);
        if (curr->right)
            al[curr->val].push_back(curr->right->val), dfs(al, curr->right, curr);
    }

public:
    int amountOfTime(TreeNode *root, int start)
    {
        vector<vector<int>> al(100001);
        dfs(al, root);

        vector<int> seen(100001);
        queue<int> q;
        q.push(start);
        seen[start] = 1;
        int rv = 0;
        while (q.size())
        {
            auto s = q.size();
            while (s)
            {
                auto n = q.front();
                q.pop();

                for (auto &nn : al[n])
                    if (!seen[nn])
                        seen[nn] = 1, q.push(nn);
                --s; 
            }

            if (q.size())
                ++rv;
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