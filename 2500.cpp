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
    int deleteGreatestValue(vector<vector<int>> &grid)
    {
        int m = grid.size(), n = grid[0].size(), rv = 0;
        for (auto it = 0; it < n; ++it)
        {
            int mm = 0;
            for (auto i = 0; i < m; ++i)
            {
                int k = 0, mmm = 0;
                for (auto j = 0; j < n; ++j)
                    if (grid[i][j] != -1 && grid[i][j] > mmm)
                        mmm = grid[i][j], k = j;
                mm = max(mm, mmm);
                grid[i][k] = -1;
            }
            rv += mm;
        }
        return rv; 
    }
};

int main()
{
    Solution sol;
    int r;

    [[],[35,21,13,21,72]]


    r = sol.deleteGreatestValue(vector<vector<int>>() = {{58,42,8,75,28}, {3, 3, 1}});
    cout << r << endl;


    r = sol.deleteGreatestValue(vector<vector<int>>() = {{1, 2, 4}, {3, 3, 1}});
    cout << r << endl;
}