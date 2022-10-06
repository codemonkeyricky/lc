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
    void dfs(vector<vector<int>> &al, vector<int> &quiet, int k, int q, vector<int> &seen)
    {
        if (quiet[q] < quiet[seen[k]])
        {
            seen[k] = q;
            for (auto &n : al[k])
                dfs(al, quiet, n, q, seen);
        }
    }

public:
    vector<int> loudAndRich(vector<vector<int>> &richer, vector<int> &quiet)
    {
        int n = quiet.size();
        quiet.push_back(1e9);
        vector<vector<int>> al(n);
        vector<int> seen(n + 1, n);

        for (auto &relative : richer)
        {
            auto rich = relative[0], poor = relative[1];
            al[rich].push_back(poor);
        }

        for (auto i = 0; i < n; ++i)
            dfs(al, quiet, i, i, seen);
        
        seen.pop_back();

        return seen;
    }
};

int main()
{
    Solution sol;
    int r;

    sol.loudAndRich(vector<vector<int>>() = {{1, 0}, {2, 1}, {3, 1}, {3, 7}, {4, 3}, {5, 3}, {6, 3}}, vector<int>() = {3, 2, 5, 4, 6, 1, 7, 0});
    cout << r << endl;
}