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
    set<array<int,2>> seen;

    bool dfs(int x, int y)
    {
        if (x == 1 && y == 1)
            return true;

        if (x % 2 == 0)
            return dfs(x / 2, y);

        if (y % 2 == 0)
            return dfs(x, y / 2);

        if (x > y)
            return dfs(y, x);

        if (seen.count({x, y}))
            return false;

        seen.insert({x, y});
        return dfs(x, x + y);
    }

public:
    bool isReachable(int x, int y)
    {
        return dfs(x, y);
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.isReachable(4, 7);
    cout << r << endl;
}