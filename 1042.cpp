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
    void dfs(vector<vector<int>> &al, vector<int> &colors, int k)
    {
        unordered_set<int> avail = {1, 2, 3, 4};
        for (auto &n : al[k])
            if (colors[n])
                avail.erase(colors[n]);
        colors[k] = *begin(avail);
        for (auto &n : al[k])
            if (!colors[n])
                dfs(al, colors, n);
    }

public:
    vector<int> gardenNoAdj(int n, vector<vector<int>> &paths)
    {
        vector<vector<int>> al(n);
        for (auto &p : paths)
            al[p[0] - 1].push_back(p[1] - 1), al[p[1] - 1].push_back(p[0] - 1);

        vector<int> colors(n);
        for (auto i = 0; i < n; ++i)
            if (!colors[i])
                dfs(al, colors, i);
        return colors;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}