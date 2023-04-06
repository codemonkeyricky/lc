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
public:
    bool isToeplitzMatrix(vector<vector<int>> &mat)
    {
        int m = mat.size(), n = mat[0].size();
        unordered_map<int, int> dp;
        for (auto i = 0; i < m; ++i)
            for (auto j = 0; j < n; ++j)
                if (!dp.count(i - j))
                    dp[i - j] = mat[i][j];
                else if (dp[i - j] != mat[i][j])
                    return false;
        return true;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}