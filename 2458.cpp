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
    vector<int> height;

    int dfs(TreeNode *curr)
    {
        if (curr)
            return height[curr->val] = 1 + max(dfs(curr->left), dfs(curr->right));
        return -1;
    }

public:
    vector<int> treeQueries(TreeNode *root, vector<int> &queries)
    {
        height = vector<int>(100001);
        unordered_map<int, vector<int>> qq;
        for (auto i = 0; i < queries.size(); ++i)
            qq[queries[i]].push_back(i);

        dfs(root);

        queue<TreeNode *> q;
        int h = 1;
        vector<int> rv(queries.size());
        q.push(root);
        while (q.size())
        {
            auto s = q.size();
            set<array<int, 2>> subtree;
            vector<int> list;
            while (s)
            {
                auto n = q.front();
                q.pop();
                if (n->left)
                    q.push(n->left), subtree.insert({height[n->left->val], n->left->val}), list.push_back(n->left->val);
                if (n->right)
                    q.push(n->right), subtree.insert({height[n->right->val], n->right->val}), list.push_back(n->right->val);
                --s;
            }

            while (list.size())
            {
                auto n = list.back();
                list.pop_back();
                if (qq.count(n))
                {
                    for (auto &q : qq[n])
                        if ((*prev(end(subtree)))[1] != n)
                            rv[q] = (*prev(end(subtree)))[0] + h;
                        else if (subtree.size() > 1)
                            rv[q] = (*prev(prev(end(subtree))))[0] + h;
                        else
                            rv[q] = h - 1;
                }
            }
            ++h;
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    vector<int> r;

    r = sol.treeQueries(vector<int>() = {5, 8, 9, 2, 1, 3, 7, 4, 6}, vector<int>() = {3, 2, 4, 8});
    for (auto &c : r)
        cout << c << ", ";
    cout << endl;
}