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
    int minimumVisitedCells(vector<vector<int>> &grid)
    {
        int m = grid.size(), n = grid[0].size();
        vector<set<int>> to_visit_x(m);
        for (auto i = 0; i < m; ++i)
            for (auto j = 0; j < n; ++j)
                to_visit_x[i].insert(j);

        vector<set<int>> to_visit_y(n);
        for (auto i = 0; i < n; ++i)
            for (auto j = 0; j < m; ++j)
                to_visit_y[i].insert(j);

        queue<array<int, 2>> q;
        q.push({0, 0});
        to_visit_x[0].erase(0);
        to_visit_y[0].erase(0);

        int rv = 1;
        while (q.size())
        {
            auto s = q.size();
            while (s)
            {
                auto [i, j] = q.front();
                q.pop();

                if (i == m - 1 && j == n - 1)
                    return rv;

                auto k = to_visit_x[i].lower_bound(j);
                for (; k != to_visit_x[i].end() && *k <= grid[i][j] + j; to_visit_x[i].erase(k++))
                    q.push({i, *k});

                k = to_visit_y[j].lower_bound(i);
                for (; k != to_visit_y[j].end() && *k <= grid[i][j] + i; to_visit_y[j].erase(k++))
                    q.push({*k, j});

                --s; 
            }
            ++rv;
        }
        return -1;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minimumVisitedCells(vector<vector<int>>() = {{7, 12, 11, 11, 4}, {10, 5, 16, 15, 7}, {7, 9, 6, 16, 7}, {1, 13, 3, 16, 0}});
    cout << r << endl;

    r = sol.minimumVisitedCells(vector<vector<int>>() = {{2, 1, 0}, {1, 0, 0}});
    cout << r << endl;

    r = sol.minimumVisitedCells(vector<vector<int>>() = {{3, 4, 2, 1}, {4, 2, 3, 1}, {2, 1, 0, 0}, {2, 4, 0, 0}});
    cout << r << endl;
}