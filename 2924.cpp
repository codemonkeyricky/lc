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
    void dfs(vector<vector<int>> &al, int u, set<int> &roots, vector<int> &seen)
    {
        if (!seen[u])
        {
            seen[u] = true;
            if (al[u].empty())
                roots.insert(u);
            else
                for (auto &v : al[u])
                    dfs(al, v, roots, seen);
        }
    }

public:
    int findChampion(int n, vector<vector<int>> &edges)
    {
        vector<vector<int>> al(n);
        for (auto &e : edges)
            al[e[1]].push_back(e[0]);

        set<int> roots;
        vector<int> seen(n);
        for (auto i = 0; i < n; ++i)
            dfs(al, i, roots, seen);

        return roots.size() == 1 ? *begin(roots) : -1;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}