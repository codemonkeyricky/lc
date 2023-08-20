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
    int bcount(set<array<int, 2>> &coords, int i, int j)
    {
        return coords.count({i, j}) + coords.count({i + 1, j}) + coords.count({i, j + 1}) + coords.count({i + 1, j + 1});
    }

    int _m, _n;

public:
    vector<long long> countBlackBlocks(int m, int n, vector<vector<int>> &coordinates)
    {
        _m = m, _n = n;

        set<array<int, 2>> coords;
        for (auto &c : coordinates)
            coords.insert({c[0], c[1]});
        
        vector<long long> rv(5);
        rv[0] = ((long long)m - 1) * (n - 1);
        set<array<int, 2>> visited;
        for (auto [i, j] : coords)
            for (int x = -1; x <= 0; ++x)
                for (int y = -1; y <= 0; ++y)
                    if (!visited.count({i + x, j + y}))
                        if (i + x >= 0 && i + x < _m && j + y >= 0 && j + y < _n)
                            if (i + x + 1 >= 0 && i + x + 1 < _m && j + y + 1 >= 0 && j + y + 1 < _n)
                                ++rv[bcount(coords, i + x, j + y)], visited.insert({{i + x, j + y}}), --rv[0];

        return rv;
    }
};

int main()
{
    Solution sol;
    vector<long long> r;

    r = sol.countBlackBlocks(3, 3, vector<vector<int>>() = {{0, 0}, {1, 1}, {0, 2}});

    r = sol.countBlackBlocks(3, 3, vector<vector<int>>() = {{0, 0}});
}