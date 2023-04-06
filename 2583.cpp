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
    long long kthLargestLevelSum(TreeNode *root, int k)
    {
        queue<TreeNode *> q;
        vector<long long> levels;
        q.push(root);
        while (q.size())
        {
            auto s = q.size();
            long long sum = 0;
            while (s)
            {
                auto n = q.front(); 
                q.pop();

                sum += n->val;
                if (n->left)
                    q.push(n->left);
                if (n->right)
                    q.push(n->right);
                --s;
            }
            levels.push_back(sum);
        }

        if (k >= levels.size())
            return -1;

        int n = levels.size();
        nth_element(begin(levels), begin(levels) + k - 1, end(levels), greater<long long>());
        return levels[k - 1];
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}