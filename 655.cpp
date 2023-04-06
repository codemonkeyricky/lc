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

class Solution
{
    int depth(TreeNode *root, int d = 1)
    {
        if (root)
            return max(depth(root->left, d + 1), depth(root->right, d + 1));
        return d;
    }

    void dfs(TreeNode *root, int i, int j, int h, vector<vector<string>> &rv)
    {
        if (root)
        {
            rv[i][j] = to_string(root->val);
            dfs(root->left, i + 1, j - (1 << (h - i - 1)), h, rv);
            dfs(root->right, i + 1, j + (1 << (h - i - 1)), h, rv);
        }
    }

public:
    vector<vector<string>> printTree(TreeNode *root)
    {
        int h = depth(root);
        int n = (1 << h) - 1;
        vector<vector<string>> rv(h, vector<string>(n));
        dfs(root, 0, (n - 1) / 2, h, rv);
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}