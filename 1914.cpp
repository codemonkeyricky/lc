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
    vector<vector<int>> visited;

    void cycRotate(vector<vector<int>> &g, int i, int j, int k)
    {
        int ci = i, cj = j;
        int m = g.size(), n = g[0].size();
        vector<int> off = {0, 1, 0, -1, 0};
        vector<int> ring;
        int skip = false;
        for (auto k = 0; k < 4; ++k)
        {
            while (true)
            {
                if (!skip)
                    ring.push_back(g[i][j]);
                visited[i][j] = 1;
                auto ni = i + off[k + 0];
                auto nj = j + off[k + 1];
                if (!(ni >= 0 && ni < m && nj >= 0 && nj < n && !visited[ni][nj]))
                {
                    skip = true;
                    break;
                }
                else
                    skip = false, i = ni, j = nj;
            }
        }
        rotate(begin(ring), begin(ring) + k % ring.size(), end(ring));

        i = ci, j = cj, skip = false;
        for (auto k = 0, l = 0; k < 4; ++k)
        {
            while (true)
            {
                if (!skip)
                    g[i][j] = ring[l++];
                visited[i][j] = 2;
                auto ni = i + off[k + 0];
                auto nj = j + off[k + 1];
                if (!(ni >= 0 && ni < m && nj >= 0 && nj < n && visited[ni][nj] != 2))
                {
                    skip = true;
                    break;
                }
                else
                    skip = false, i = ni, j = nj;
            }
        }
    }

public:
    vector<vector<int>> rotateGrid(vector<vector<int>> &grid, int k)
    {
        int m = grid.size(), n = grid[0].size();
        visited = vector<vector<int>>(m , vector<int>(n));

        for (auto i = 0; i < m; ++i)
            for (auto j = 0; j < n; ++j)
                if (!visited[i][j])
                    cycRotate(grid, i, j, k);
        return grid;
    }
};

int main()
{
    Solution sol;
    vector<vector<int>> rv;

    rv = sol.rotateGrid(vector<vector<int>>() = {
                            {1, 2, 3, 4},
                            {5, 6, 7, 8},
                            {9, 10, 11, 12},
                            {13, 14, 15, 16}},
                        2);
    for (auto &row : rv)
    {
        for (auto &c : row)
            cout << c << " ";
        cout << endl; 
    }
}