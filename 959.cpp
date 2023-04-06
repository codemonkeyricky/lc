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
    vector<int> parents;
    int m, n;

    int find(int k)
    {
        if (parents[k] < 0)
            return k;
        return parents[k] = find(parents[k]);
    }

    void unionize(array<int, 3> a, array<int, 3> b)
    {
        if (a[0] >= 0 && a[0] < m && a[1] >= 0 && a[1] < n && b[0] >= 0 && b[0] < m && b[1] >= 0 && b[1] < n)
        {
            auto p1 = find((a[0] * m + a[1]) * 4 + a[2]);
            auto p2 = find((b[0] * m + b[1]) * 4 + b[2]);
            if (p1 != p2)
            {
                if (parents[p1] > parents[p2])
                    swap(p1, p2);

                parents[p1] += parents[p2];
                parents[p2] = p1;
            }
        }
    }

public:
    int regionsBySlashes(vector<string> &grid)
    {
        m = grid.size(), n = grid[0].size();
        parents = vector<int>(m * n * 4, -1);
        for (auto i = 0; i < m; ++i)
            for (auto j = 0; j < n; ++j)
                if (grid[i][j] == '/')
                {
                    unionize({i, j, 0}, {i, j, 3});
                    unionize({i, j, 0}, {i - 1, j, 2});
                    unionize({i, j, 3}, {i, j - 1, 1});

                    unionize({i, j, 1}, {i, j, 2});
                    unionize({i, j, 1}, {i, j + 1, 3});
                    unionize({i, j, 2}, {i + 1, j, 0});
                }
                else if (grid[i][j] == '\\')
                {
                    unionize({i, j, 0}, {i, j, 1});
                    unionize({i, j, 0}, {i - 1, j, 2});
                    unionize({i, j, 1}, {i, j + 1, 3});

                    unionize({i, j, 2}, {i, j, 3});
                    unionize({i, j, 2}, {i + 1, j, 0});
                    unionize({i, j, 3}, {i, j - 1, 1});
                }
                else
                {
                    unionize({i, j, 0}, {i, j, 1});
                    unionize({i, j, 0}, {i, j, 2});
                    unionize({i, j, 0}, {i, j, 3});

                    unionize({i, j, 0}, {i - 1, j, 2});
                    unionize({i, j, 2}, {i + 1, j, 0});
                    unionize({i, j, 3}, {i, j - 1, 1});
                    unionize({i, j, 1}, {i, j + 1, 3});
                }

        set<int> uniq;
        for (auto i = 0; i < m; ++i)
            for (auto j = 0; j < n; ++j)
                for (auto k = 0; k < 4; ++k)
                    uniq.insert(find((i * m + j) * 4 + k));

        return uniq.size();
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.regionsBySlashes(vector<string>() = {" /", "/ "});
    cout << r << endl;
}