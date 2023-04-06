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
    int sort_array(vector<int> &array)
    {
        int n = array.size();
        unordered_map<int, int> index;
        for (auto i = 0; i < array.size(); ++i)
            index[array[i]] = i;
        auto sorted = array;
        sort(begin(sorted), end(sorted));

        int rv = 0;
        for (auto i = 0; i < n; ++i)
            if (index[sorted[i]] != i && ++rv)
            {
                swap(index[sorted[i]], index[array[i]]);
                swap(array[index[sorted[i]]], array[index[array[i]]]);
            }

        return rv;
    }
    int minimumOperations(TreeNode *root)
    {
        queue<TreeNode *> q;
        q.push(root);
        int rv = 0;
        while (q.size())
        {
            auto s = q.size();
            vector<int> array;
            while (s)
            {
                auto n = q.front();
                array.push_back(n->val);
                q.pop();
                if (n->left)
                    q.push(n->left);
                if (n->right)
                    q.push(n->right);
                --s;
            }
            rv += sort_array(array);
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.sort_array(vector<int>() = {20, 46, 15, 39});
    cout << r << endl;

    r = sol.sort_array(vector<int>() = {7, 6, 8, 5});
    cout << r << endl;
}