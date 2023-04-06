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
    void dfs(vector<vector<int>> &mat, int i, int j, int src, int dst)
    {
        int m = mat.size();
        int n = mat[0].size();
        vector<int> off = {-1, 0, 1, 0, -1};
        mat[i][j] = dst;
        for (auto k = 0; k < 4; ++k)
        {
            int ni = i + off[k + 0];
            int nj = j + off[k + 1];
            if (ni >= 0 && ni < m && nj >= 0 && nj < n && mat[ni][nj] == src)
                dfs(mat, ni, nj, src, dst);
        }
    }

public:
    vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc, int color)
    {
        dfs(image, sr, sc, image[sr][sc], color);
        return image;
    }
};

int main()
{
    Solution sol;
    int r;

    sol.floodFill(vector<vector<int>>() = {{0, 0, 0}, {0, 0, 0}}, 0, 0, 0);
    cout << r << endl;

    sol.floodFill(vector<vector<int>>() = {{1, 1, 1}, {1, 1, 0}, {1, 0, 1}}, 1, 1, 2);
    cout << r << endl;
}