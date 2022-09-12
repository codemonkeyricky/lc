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
    vector<vector<char>> rotateTheBox(vector<vector<char>> &box)
    {
        int m = box.size(), n = box[0].size();
        for (auto k = 0; k < m; ++k)
            for (int i = n - 1, j = n - 1; i >= -1; --i)
                if (i >= 0 && box[k][i] == '#')
                    box[k][j--] = box[k][i];
                else if (i == -1 || box[k][i] == '*')
                {
                    while (i != j)
                        box[k][j--] = '.';
                    --j;
                }

        vector<vector<char>> rv(n, vector<char>(m));
        for (auto i = 0; i < m; ++i)
            for (auto j = 0; j < n; ++j)
                rv[j][m - i - 1] = box[i][j];

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    sol.rotateTheBox(vector<vector<char>>() = {{'#', '.', '*', '.'}});

    sol.rotateTheBox(vector<vector<char>>() = {{'#', '.', '#'}});
}