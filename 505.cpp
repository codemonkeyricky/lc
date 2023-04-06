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
    int shortestDistance(vector<vector<int>> &maze, vector<int> &src, vector<int> &dst)
    {
        priority_queue<array<int, 3>, vector<array<int, 3>>, greater<array<int, 3>>> q;
        q.push({0, src[0], src[1]});
        int m = maze.size(), n = maze[0].size();
        vector<vector<int>> seen(m, vector<int>(n, 1e9));
        seen[src[0]][src[1]] = 1;
        vector<int> off = {0, -1, 0, 1, 0};
        while (q.size())
        {
            auto [d, i, j] = q.top(); 
            q.pop();

            for (auto k = 0; k < 4; ++k)
            {
                int ni = i, nj = j, steps = 0;
                while (true)
                {
                    auto nni = ni + off[k + 0];
                    auto nnj = nj + off[k + 1];

                    if (nni >= 0 && nni < m && nnj >= 0 && nnj < n && !maze[nni][nnj])
                        ni = nni, nj = nnj;
                    else
                        break;
                    ++steps;
                }

                if (d + steps < seen[ni][nj])
                {
                    seen[ni][nj] = d + steps;
                    q.push({d + steps, ni, nj});
                }
            }
        }
        return seen[dst[0]][dst[1]] != 1e9 ? seen[dst[0]][dst[1]] : -1;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.shortestDistance(vector<vector<int>>() = {{0, 0, 1, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 1, 0}, {1, 1, 0, 1, 1}, {0, 0, 0, 0, 0}}, vector<int>() = {0, 4}, vector<int>() = {4, 4});
    cout << r << endl;
}