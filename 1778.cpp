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

/**
 * // This is the GridMaster's API interface.
 * // You should not implement it, or speculate about its implementation
 * class GridMaster {
 *   public:
 *     bool canMove(char direction);
 *     void move(char direction);
 *     boolean isTarget();
 * };
 */

class Solution
{
    int dfs(GridMaster &m, int i = 0, int j = 0)
    {
        int rv = 1e9;
        map[i][j] = m.isTarget() ? 2 : 1;
        for (auto k = 0; k < 4; ++k)
        {
            int ni = i + off[k + 0];
            int nj = j + off[k + 1];
            if (m.canMove(dir[k]) && !map[ni].count(nj))
            {
                m.move(dir[k]);
                dfs(m, ni, nj);
                m.move(odir[k]);
            }
        }

        return rv;
    }

    vector<char> dir = {'U', 'R', 'D', 'L'};
    vector<char> odir = {'D', 'L', 'U', 'R'};
    vector<int> off = {-1, 0, 1, 0, -1};
    unordered_map<int, unordered_map<int, int>> map;
    unordered_map<int, unordered_set<int>> seen; 

public:
    int findShortestPath(GridMaster &master)
    {
        dfs(master);

        vector<array<int,2>> q; 
        q.push_back({0, 0});
        int rv = 0;
        while (q.size())
        {
            auto s = q.size();
            while (s)
            {
                auto [i, j] = q.front();
                q.pop_back();

                if (map[i][j] == 2)
                    return rv;

                for (auto k = 0; k < 4; ++k)
                {
                    auto ni = i + off[k + 0];
                    auto nj = j + off[k + 1];

                    if (map[ni][nj])
                        if (!seen[ni].count(nj))
                            seen[ni].insert(nj), q.push_back({ni, nj});
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

    cout << r << endl;
}