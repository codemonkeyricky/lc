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
    vector<vector<int>> queensAttacktheKing(vector<vector<int>> &queens, vector<int> &king)
    {
        vector<int> offset = {0, -1, 0, 1, 0};
        vector<int> offset2 = {1, 1, -1, -1, 1};
        vector<vector<int>> rv;

        set<array<int,2>> otherQueen;
        for (auto &q : queens)
            otherQueen.insert({q[0], q[1]});

        for (auto &q : queens)
        {
            for (auto k = 0; k < 4; ++k)
            {
                int attack = 1;
                auto i = q[0], j = q[1];
                while (i >= 0 && j >= 0 && i < 8 && j < 8 && attack)
                {
                    auto ni = i + offset[k + 0];
                    auto nj = j + offset[k + 1];
                    if (ni == king[0] && nj == king[1])
                        rv.push_back(q), attack = false;
                    else if (otherQueen.count({ni, nj}))
                        attack = false;
                    i = ni, j = nj;
                }
            }

            for (auto k = 0; k < 4; ++k)
            {
                auto i = q[0], j = q[1], attack = 1;
                while (i >= 0 && j >= 0 && i < 8 && j < 8 && attack)
                {
                    auto ni = i + offset2[k + 0];
                    auto nj = j + offset2[k + 1];
                    if (ni == king[0] && nj == king[1])
                        rv.push_back(q), attack = false;
                    else if (otherQueen.count({ni, nj}))
                        attack = false;
                    i = ni, j = nj;
                }
            }
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    sol.queensAttacktheKing(vector<vector<int>>() = {{0, 1}, {1, 0}, {4, 0}, {0, 4}, {3, 3}, {2, 4}}, vector<int>() = {0, 0});

    sol.queensAttacktheKing(vector<vector<int>>() = {{0, 1}, {1, 0}, {4, 0}, {0, 4}, {3, 3}, {2, 4}}, vector<int>() = {0, 0});
}