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
    vector<int> dfs(TreeNode *curr, int k, int &rv)
    {
        vector<int> q;
        if (curr)
        {
            auto l = dfs(curr->left, k, rv);
            auto r = dfs(curr->right, k, rv);
            q.insert(end(q), begin(l), end(l));
            q.insert(end(q), begin(r), end(r));
            q.push_back(curr->val);
            sort(begin(q), end(q));
            if (q.size() > k)
                q.resize(k);
            auto d = lower_bound(begin(q), end(q), curr->val) - begin(q);
            if (d >= k)
                ++rv;
        }
        return q;
    }

public:
    int countGreatEnoughNodes(TreeNode *root, int k)
    {
        int rv = 0;
        dfs(root, k, rv);
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}