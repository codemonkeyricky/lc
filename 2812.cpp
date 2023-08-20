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
    int maximumSafenessFactor(vector<vector<int>> &grid)
    {
        int m = grid.size(), n = grid[0].size();
        vector<int> dir = {0, 1, 0, -1, 0};

        queue<array<int, 3>> mdq;
        vector<vector<int>> md(m, vector<int>(n, 1e9));
        for (auto i = 0; i < m; ++i)
            for (auto j = 0; j < n; ++j)
                if (grid[i][j])
                    mdq.push({0, i, j}), md[i][j] = 0;
        while (mdq.size())
        {
            auto [d, i, j] = mdq.front(); 
            mdq.pop();

            for (auto k = 0; k < 4; ++k)
            {
                auto x = i + dir[k + 0];
                auto y = j + dir[k + 1];
                if (x >= 0 && x < m && y >= 0 && y < n && d + 1 < md[x][y])
                {
                    md[x][y] = d + 1;
                    mdq.push({d + 1, x, y});
                }
            }
        }

        priority_queue<array<int, 3>> q;
        vector<vector<int>> seen(m, vector<int>(n, 1e9));
        q.push({md[0][0], 0, 0});
        seen[0][0] = md[0][0];
        while (q.size())
        {
            auto [d, i, j] = q.top();
            q.pop();
            if (i == m - 1 && j == n - 1)
                return d;

            for (auto k = 0; k < 4; ++k)
            {
                auto x = i + dir[k + 0];
                auto y = j + dir[k + 1];
                if (x >= 0 && x < m && y >= 0 && y < n)
                {
                    auto dd = min(d, md[x][y]);
                    if (dd < seen[x][y])
                    {
                        if (seen[x][y] != 1e9)
                            assert(0);
                        seen[x][y] = dd; 
                        q.push({dd, x, y});
                    }
                }
            }
        }
        return -1;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.maximumSafenessFactor(vector<vector<int>>() = {{0, 0, 0}, {0, 0, 0}, {0, 0, 1}});
    cout << r << endl;

    r = sol.maximumSafenessFactor(vector<vector<int>>() = {{1, 0, 0}, {0, 0, 0}, {0, 0, 1}});
    cout << r << endl;

    r = sol.maximumSafenessFactor(vector<vector<int>>() = {{0, 0, 0, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {1, 0, 0, 0}});
    cout << r << endl;

    r = sol.maximumSafenessFactor(vector<vector<int>>() = {{0, 0, 1}, {0, 0, 0}, {0, 0, 0}});
    cout << r << endl;
}