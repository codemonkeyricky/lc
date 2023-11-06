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
    long long dfs(vector<vector<int>> &al, vector<int> &values, int p, int u)
    {
        long long sum = 0, children = 0;
        for (auto &v : al[u])
            if (v != p)
                sum += dfs(al, values, u, v), ++children;
        return min(children ? sum : (long long)1e9, (long long)values[u]);
    }

public:
    long long maximumScoreAfterOperations(vector<vector<int>> &edges, vector<int> &values)
    {
        int n = values.size();
        vector<vector<int>> al(n);

        for (auto &e : edges)
            al[e[0]].push_back(e[1]),
                al[e[1]].push_back(e[0]);

        long long sum = dfs(al, values, -1, 0);
        return accumulate(begin(values), end(values), 0ll) - sum;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.maximumScoreAfterOperations(vector<vector<int>>() = {{0, 1}, {0, 2}, {1, 3}, {1, 4}, {2, 5}, {2, 6}}, vector<int>() = {20, 10, 9, 7, 4, 3, 5});
    cout << r << endl;

    r = sol.maximumScoreAfterOperations(vector<vector<int>>() = {{0, 1}, {0, 2}, {0, 3}, {2, 4}, {4, 5}}, vector<int>() = {5, 2, 5, 2, 1, 1});
    cout << r << endl;
}