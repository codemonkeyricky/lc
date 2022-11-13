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

/*
 * // This is the custom function interface.
 * // You should not implement it, or speculate about its implementation
 * class CustomFunction {
 * public:
 *     // Returns f(x, y) for any given positive integers x and y.
 *     // Note that f(x, y) is increasing with respect to both x and y.
 *     // i.e. f(x, y) < f(x + 1, y), f(x, y) < f(x, y + 1)
 *     int f(int x, int y);
 * };
 */

class Solution
{
public:
    vector<vector<int>> findSolution(CustomFunction &func, int z)
    {
        vector<vector<int>> rv;
        priority_queue<array<int, 3>, vector<array<int, 3>>, greater<array<int, 3>>> q;
        q.push({func.f(0, 0), 0, 0});
        int seen[1001][1001] = {};
        while (q.size())
        {
            auto [zz, x, y] = q.top();
            q.pop();
            if (zz == z)
                rv.push_back({x, y});
            if (zz > z)
                break;
            if (!seen[x + 1][y] && seen[x + 1][y] = 1)
                q.push({func.f(x + 1, y), x + 1, y}),
                    if (!seen[x][y + 1] && seen[x][y + 1] = 1)
                        q.push({func.f(x, y + 1), x, y + 1});
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}
