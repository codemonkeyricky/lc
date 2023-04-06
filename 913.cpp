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
    vector<array<int, 3>> parents(vector<vector<int>> &graph, int m, int c, int t)
    {
        vector<array<int, 3>> rv;
        if (t == 2)
            for (int m2 : graph[m])
                rv.push_back({m2, c, 3 - t});
        else
            for (int c2 : graph[c])
                if (c2 > 0)
                    rv.push_back({m, c2, 3 - t});
        return rv;
    }

public:
    int catMouseGame(vector<vector<int>> graph)
    {
        int n = graph.size();
        int DRAW = 0, MOUSE = 1, CAT = 2;

        int color[51][51][3] = {};
        int degree[51][51][3] = {};

        // degree[node] : the number of neutral children of this node
        for (int m = 0; m < n; ++m)
            for (int c = 0; c < n; ++c)
            {
                degree[m][c][1] = graph[m].size();
                degree[m][c][2] = graph[c].size();
                for (int x : graph[c])
                    if (x == 0)
                    {
                        degree[m][c][2]--;
                        break;
                    }
            }

        // enqueued : all nodes that are colored
        queue<array<int, 4>> q;
        for (int i = 0; i < n; ++i)
            for (int t = 1; t <= 2; ++t)
            {
                color[0][i][t] = MOUSE;
                q.push({0, i, t, MOUSE});
                if (i > 0)
                {
                    color[i][i][t] = CAT;
                    q.push({i, i, t, CAT});
                }
            }

        // percolate
        while (q.size())
        {
            // for nodes that are colored
            auto [i, j, t, c] = q.front();
            q.pop();

            // for every parent of this node i, j, t
            for (auto &[i2, j2, t2] : parents(graph, i, j, t))
            {
                // if this parent is not colored
                if (color[i2][j2][t2] == DRAW)
                {
                    // if the parent can make a winning move (ie. mouse to MOUSE), do so
                    if (t2 == c)
                    {
                        color[i2][j2][t2] = c;
                        q.push({i2, j2, t2, c});
                    }
                    else
                    {
                        // else, this parent has degree[parent]--, and enqueue
                        // if all children of this parent are colored as losing moves
                        --degree[i2][j2][t2];
                        if (degree[i2][j2][t2] == 0)
                        {
                            color[i2][j2][t2] = 3 - t2;
                            q.push({i2, j2, t2, 3 - t2});
                        }
                    }
                }
            }
        }

        return color[1][2][1];
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.catMouseGame(vector<vector<int>>() = {{5, 7, 9}, {3, 4, 5, 6}, {3, 4, 5, 8}, {1, 2, 6, 7}, {1, 2, 5, 7, 9}, {0, 1, 2, 4, 8}, {1, 3, 7, 8}, {0, 3, 4, 6, 8}, {2, 5, 6, 7, 9}, {0, 4, 8}});
    cout << r << endl;

    r = sol.catMouseGame(vector<vector<int>>() = {{2, 3}, {3, 4}, {0, 4}, {0, 1}, {1, 2}});
    cout << r << endl;

    r = sol.catMouseGame(vector<vector<int>>() = {{1, 3}, {0}, {3}, {0, 2}});
    cout << r << endl;

    r = sol.catMouseGame(vector<vector<int>>() = {{2, 5}, {3}, {0, 4, 5}, {1, 4, 5}, {2, 3}, {0, 2, 3}});
    cout << r << endl;
}