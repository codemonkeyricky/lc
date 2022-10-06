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
    int totalNQueens(int n, int row = 0, int col = 0, int diag = 0, int adiag = 0)
    {
        if (row >= n)
            return 1;

        int rv = 0;
        for (auto j = 0; j < n; ++j)
            if (!((1 << j) & col) && !((1 << (row - j + n)) & diag) && !(1 << (row + j) & adiag))
                rv += totalNQueens(n, row + 1, col | (1 << j), (1 << (row - j + n)) | diag, (1 << (row + j)) | adiag);
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.totalNQueens(4);
    cout << r << endl;
}