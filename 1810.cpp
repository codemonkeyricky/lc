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

// This is the costMaster's API interface.
// You should not implement it, or speculate about its implementation
class GridMaster
{
public:
    bool canMove(char direction);
    int move(char direction);
    bool isTarget();
};

class Solution
{
    unordered_map<int, unordered_map<int, int>> cost;

    vector<int> off = {0, -1, 0, 1, 0};
    array<int, 2> target = {}, empty = {};

    void dfs(GridMaster &m, int i, int j)
    {
        vector<char> dir = {'L', 'D', 'R', 'U'};
        for (auto k = 0; k < 4; ++k)
        {
            auto ni = i + off[k + 0];
            auto nj = j + off[k + 1];
            if (!cost[ni].count(nj))
            {
                if (m.canMove(dir[k]))
                {
                    cost[ni][nj] = m.move(dir[k]);
                    if (m.isTarget())
                        target = {ni, nj};
                    dfs(m, ni, nj);
                    m.move(dir[(k + 2) % 4]);
                }
                else
                    cost[ni][nj] = 0;
            }
        }
    }

public:
    int findShortestPath(GridMaster &m)
    {
        dfs(m, 0, 0);

        priority_queue<array<int, 3>, vector<array<int, 3>>, greater<array<int, 3>>> q;
        q.push({0, 0, 0});

        unordered_map<int, unordered_map<int, int>> dp;
        cost[0][0] = dp[0][0] = 0;
        while (q.size())
        {
            auto [d, i, j] = q.top();
            q.pop();
            for (auto k = 0; k < 4; ++k)
            {
                int ni = i + off[k + 0];
                int nj = j + off[k + 1];
                if (cost[ni][nj])
                    if (!dp[ni].count(nj) || d + cost[ni][nj] < dp[ni][nj])
                    {
                        dp[ni][nj] = d + cost[ni][nj];
                        q.push({dp[ni][nj], ni, nj});
                    }
            }
        }

        return (target == empty || !dp[target[0]].count(target[1])) ? -1 : dp[target[0]][target[1]];
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}