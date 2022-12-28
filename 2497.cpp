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
    int maxStarSum(vector<int> &vals, vector<vector<int>> &edges, int k)
    {
        int n = vals.size();
        vector<set<array<int, 2>>> al(n);
        for (auto &e : edges)
            al[e[0]].insert({vals[e[1]], e[1]}),
                al[e[1]].insert({vals[e[0]], e[1]});

        int rv = -1e9;
        for (auto i = 0, kk = k - 1, sum = vals[i]; i < n; ++i, kk = k - 1, sum = vals[i])
        {
            rv = max(rv, sum);
            for (auto it = rbegin(al[i]); it != rend(al[i]) && kk >= 0; --kk, ++it)
                rv = max(rv, sum += (*it)[0]);
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.maxStarSum(vector<int>() = {-5}, vector<vector<int>>() = {}, 0);
    cout << r << endl;

    r = sol.maxStarSum(vector<int>() = {1, 2, 3, 4, 10, -10, -20}, vector<vector<int>>() = {{0, 1}, {1, 2}, {1, 3}, {3, 4}, {3, 5}, {3, 6}}, 2);
    cout << r << endl;
}