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
    vector<vector<int>> imageSmoother(vector<vector<int>> &img)
    {
        int m = img.size(), n = img[0].size();
        vector<vector<int>> rv(m, vector<int>(n));
        for (auto i = 0; i < m; ++i)
            for (auto j = 0; j < n; ++j)
            {
                int sum = 0, c = 0;
                for (auto k = -1; k < 2; ++k)
                    for (auto l = -1; l < 2; ++l)
                        if (i + k >= 0 && i + k < m && j + l >= 0 && j + l < n)
                            sum += img[i + k][j + l], ++c;
                rv[i][j] = sum / c;
            }
        return rv; 
    }
};

int main()
{
    Solution sol;
    int r;

    sol.imageSmoother(vector<vector<int>>() = {{1, 1, 1}, {1, 0, 1}, {1, 1, 1}});
    cout << r << endl;
}