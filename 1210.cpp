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
    bool isAllowed(vector<vector<int>> &grid, array<int, 4>p)
    {
        int n = grid.size();
        auto [ti, tj, hi, hj] = p;
        if (ti >= 0 && ti < n && tj >= 0 && tj < n && hi >= 0 && hi < n && hj >= 0 && hj < n)
            return !grid[ti][tj] && !grid[hi][hj];
        return false;
    }

public:
    int minimumMoves(vector<vector<int>> &grid)
    {
        int n = grid.size();
        queue<array<int, 4>> q;
        set<array<int, 4>> seen;
        seen.insert({0, 0, 0, 1});
        array<int, 4> target = {n - 1, n - 2, n - 1, n - 1};
        q.push({0, 0, 0, 1});
        int rv = 0;
        while (q.size())
        {
            auto s = q.size();
            while (s)
            {
                auto p = q.front();
                auto [ti, tj, hi, hj] = q.front();
                q.pop();
                if (p == target)
                    return rv;

                array<int, 4> right = {ti, tj + 1, hi, hj + 1};
                array<int, 4> down = {ti + 1, tj, hi + 1, hj};

                // move right
                if (isAllowed(grid, right))
                    if (!seen.count(right))
                    {
                        seen.insert(right);
                        q.push(right);
                    }

                // move down
                if (isAllowed(grid, down))
                    if (!seen.count(down))
                    {
                        seen.insert(down);
                        q.push(down);
                    }

                // rotate cw
                if (tj + 1 == hj)
                {
                    array<int, 4> rotated = {ti, tj, ti + 1, tj};
                    if (isAllowed(grid, down))
                        if (!seen.count(rotated))
                        {
                            seen.insert(rotated);
                            q.push(rotated); 
                        }
                }

                // rotate ccw
                if (ti + 1 == hi)
                {
                    array<int, 4> rotated = {ti, tj, ti, tj + 1};
                    if (isAllowed(grid, right))
                        if (!seen.count(rotated))
                        {
                            seen.insert(rotated);
                            q.push(rotated); 
                        }
                }

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

    r = sol.minimumMoves(vector<vector<int>>() =
                             {{0, 0, 0, 0, 0, 1},
                              {1, 1, 0, 0, 1, 0},
                              {0, 0, 0, 0, 1, 1},
                              {0, 0, 1, 0, 1, 0},
                              {0, 1, 1, 0, 0, 0},
                              {0, 1, 1, 0, 0, 0}});
    cout << r << endl;
}