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
    vector<int> seen, depth;
    int dfs(vector<int> &edges, int k, int d)
    {
        if (edges[k] == -1)
            return -1;

        if (seen[k] == 0)
        {
            seen[k] = 1;
            depth[k] = d;
            auto r = dfs(edges, edges[k], d + 1);
            seen[k] = 2;
            return r;
        }
        else if (seen[k] == 1)
            return d - depth[k];
        else
            return -1;
    }

public:
    int longestCycle(vector<int> &edges)
    {
        seen = vector<int>(100001);
        depth = vector<int>(100001);

        int rv = -1;
        for (auto i = 0; i < edges.size(); ++i)
            rv = max(rv, dfs(edges, i, 0));
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.longestCycle(vector<int>() = {-1, 4, -1, 2, 0, 4});
    cout << r << endl;
}