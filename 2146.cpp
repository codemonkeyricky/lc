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
    vector<vector<int>> highestRankedKItems(vector<vector<int>> &grid, vector<int> &pricing, vector<int> &start, int k)
    {
        int m = grid.size(), n = grid[0].size(), d = 0;
        queue<array<int, 2>> q;
        q.push({start[0], start[1]});
        vector<int> off = {0, -1, 0, 1, 0};
        vector<vector<int>> seen(m, vector<int>(n));
        vector<vector<int>> list;
        while (q.size() && list.size() < k)
        {
            auto s = q.size();
            while (s)
            {
                auto [i, j] = q.front();
                seen[i][j] = true;
                if (pricing[0] <= grid[i][j] && grid[i][j] <= pricing[1])
                    list.push_back({d, grid[i][j], i, j});
                q.pop();
                for (auto k = 0; k < 4; ++k)
                {
                    auto ni = i + off[k + 0];
                    auto nj = j + off[k + 1];
                    if (ni >= 0 && ni < m && nj >= 0 && nj < n && !seen[ni][nj] && grid[ni][nj])
                        seen[ni][nj] = true, q.push({ni, nj});
                }
                --s;
            }
            ++d;
        }

        sort(begin(list), end(list));
        vector<vector<int>> rv;
        for (auto i = 0; i < k && i < list.size(); ++i)
            rv.push_back({list[i][2], list[i][3]});

        return rv;
    }
};

int main()
{
    Solution sol;


    sol.highestRankedKItems(vector<vector<int>>() = {{2, 0, 2}, {4, 5, 3}, {2, 0, 2}}, vector<int>() = {2, 5}, vector<int>() = {1, 1}, 9);
    sol.highestRankedKItems(vector<vector<int>>() = {{1, 1, 1}, {0, 0, 1}, {2, 3, 4}}, vector<int>() = {2, 5}, vector<int>() = {0, 0}, 3);
    sol.highestRankedKItems(vector<vector<int>>() = {{1, 2, 0, 1}, {1, 3, 0, 1}, {0, 2, 5, 1}}, vector<int>() = {2, 5}, vector<int>() = {0, 0}, 3);
}