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
public:
    TreeNode *replaceValueInTree(TreeNode *root)
    {
        queue<array<TreeNode *, 2>> q;
        q.push({nullptr, root});
        while (q.size())
        {
            auto s = q.size();
            int sum = 0;
            map<TreeNode *, int> map;
            vector<array<TreeNode *, 2>> cousins;
            while (s)
            {
                auto [parent, child] = q.front();
                q.pop();
                map[parent] += child->val;
                sum += child->val;
                if (child->left)
                    q.push({child, child->left});
                if (child->right)
                    q.push({child, child->right});

                cousins.push_back({parent, child});
                --s;
            }

            for (auto &[parent, child] : cousins)
                child->val = sum - map[parent];
        }

        return root;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}