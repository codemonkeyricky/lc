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
    bool dfs(vector<set<int>> &al, int p, int k, int l, vector<int> &seen)
    {
        if (seen[k])
            return true;

        if (l == 0)
            return false;

        seen[k] = l;
        for (auto &v : al[k])
            if (v != p)
                if (dfs(al, k, v, l - 1, seen))
                    return true;
        seen[k] = 0;

        return false;
    }

    bool cycleExist(vector<set<int>> &al, int l)
    {
        int n = al.size();
        for (auto i = 0; i < n; ++i)
        {
            vector<int> seen(n);
            if (dfs(al, -1, i, l, seen))
                return true;
        }
        return false;
    }

public:
    int findShortestCycle(int n, vector<vector<int>> &edges)
    {
        vector<set<int>> al(n);
        for (auto &e : edges)
            al[e[0]].insert(e[1]), al[e[1]].insert(e[0]);

        int l = 3, r = 1e9;
        while (l < r)
        {
            int m = (l + r) / 2;
            if (cycleExist(al, m))
                r = m;
            else
                l = m + 1;
        }
        return l == 1e9 ? -1 : l;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.findShortestCycle(6, vector<vector<int>>() = {{4, 1}, {5, 1}, {3, 2}, {5, 0}, {4, 0}, {3, 0}, {2, 1}});
    cout << r << endl;

    r = sol.findShortestCycle(7, vector<vector<int>>() = {{0, 1}, {1, 2}, {2, 0}, {3, 4}, {4, 5}, {5, 6}, {6, 3}});
    cout << r << endl;
}