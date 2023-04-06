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
    int numSpecial(vector<vector<int>> &mat)
    {
        int m = mat.size(), n = mat[0].size(); 
        vector<int> row(m), col(n);
        for (auto i = 0; i < m; ++i)
            for (auto j = 0; j < n; ++j)
                if (mat[i][j])
                    ++row[i], ++col[j];

        int rv = 0;
        for (auto i = 0; i < m; ++i)
            for (auto j = 0; j < n; ++j)
                if (mat[i][j] && row[i] == 1 && col[j] == 1)
                    ++rv;
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.numSpecial(vector<vector<int>>() = {{1, 0, 0}, {0, 0, 1}, {1, 0, 0}});
    cout << r << endl;
}