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
    // inc / path
    array<int, 2> dfs2(vector<int> &cost, int k)
    {
        int n = cost.size();
        if ((k - 1) * 2 >= n || (k - 1) * 2 + 1 >= n)
            return {0, cost[k - 1]};

        auto left = dfs2(cost, k * 2);
        auto right = dfs2(cost, k * 2 + 1);
        return {left[0] + right[0] + abs(left[1] - right[1]), max(left[1], right[1]) + cost[k - 1]};
    }

public:
    int minIncrements(int n, vector<int> &cost)
    {
        return dfs2(cost, 1)[0];
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minIncrements(7, vector<int>() = {1, 5, 2, 2, 3, 3, 1});
    cout << r << endl;
}