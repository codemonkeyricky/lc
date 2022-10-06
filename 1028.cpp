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

    TreeNode *dfs(string &traversal, int &k, int d = 0)
    {
        int n = traversal.size();

        string num; 
        while (k < n && traversal[k] != '-')
            num += traversal[k++];

        auto node = new TreeNode(stoi(num)); 

        int dd = 0;
        while (k + dd < n && traversal[k + dd] == '-')
            ++dd;

        if (dd == d + 1)
            k = k + dd, node->left = dfs(traversal, k, d + 1);

        dd = 0;
        while (k + dd < n && traversal[k + dd] == '-')
            ++dd;

        if (dd == d + 1)
            k = k + dd, node->right = dfs(traversal, k, d + 1);

        return node;
    }

public:
    TreeNode *recoverFromPreorder(string traversal)
    {
        int k = 0;
        return dfs(traversal, k);
    }
};

int main()
{
    Solution sol;

    sol.recoverFromPreorder("1-2--3--4-5--6--7");
}