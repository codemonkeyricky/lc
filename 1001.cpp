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
    vector<int> gridIllumination(int n, vector<vector<int>> &lamps, vector<vector<int>> &queries)
    {
        unordered_map<int, int> lit_col, lit_row, diag, adiag;

        set<array<int, 2>> lights;
        for (auto &l : lamps)
        {
            auto x = l[0], y = l[1];
            if (!lights.count({x, y}))
            {
                ++lit_row[x], ++lit_col[y], ++diag[y - x], ++adiag[n - y - x];
                lights.insert({x, y});
            }
        }

        vector<int> rv;
        for (auto &q : queries)
        {
            auto x = q[0], y = q[1];
            auto r = lit_row[x] || lit_col[y] || diag[y - x] || adiag[n - y - x];
            for (int i = x - 1; i < x + 2; ++i)
                for (int j = y - 1; j < y + 2; ++j)
                    if (i >= 0 && i < n && j >= 0 && j < n)
                        if (lights.count({i, j}))
                        {
                            --lit_row[i], --lit_col[j], --diag[j - i], --adiag[n - j - i];
                            lights.erase({i, j});
                        }
            rv.push_back(r);
        }
        return rv; 
    }
};

int main()
{
    Solution sol;
    int r;

    sol.gridIllumination(6, vector<vector<int>>() = {{1, 1}}, vector<vector<int>>() = {{2, 0}, {1, 0}});
    cout << r << endl;

    sol.gridIllumination(6, vector<vector<int>>() = {{2, 5}, {4, 2}, {0, 3}, {0, 5}, {1, 4}, {4, 2}, {3, 3}, {1, 0}}, vector<vector<int>>() = {{4, 3}, {3, 1}, {5, 3}, {0, 5}, {4, 4}, {3, 3}});
    cout << r << endl;
}