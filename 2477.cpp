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
    int dfs(vector<vector<int>> &al, int k, vector<int> &leafs, vector<int> &seen)
    {
        seen[k] = 1;
        leafs[k] = 1;
        for (auto &n : al[k])
            if (!seen[n])
                leafs[k] += dfs(al, n, leafs, seen);

        return leafs[k];
    }

    long long dfs2(vector<vector<int>> &al, int seats, int k, vector<int> &leafs, vector<int> &seen)
    {
        seen[k] = 1;
        long long rv = 0;
        for (auto &n : al[k])
            if (!seen[n])
            {
                rv += (leafs[n] + seats - 1) / seats;
                rv += dfs2(al, seats, n, leafs, seen);
            }
        return rv;
    }

public:
    long long minimumFuelCost(vector<vector<int>> &roads, int seats)
    {
        int n = roads.size() + 1;
        vector<vector<int>> al(n);
        for (auto &road : roads)
            al[road[0]].push_back(road[1]), al[road[1]].push_back(road[0]);

        vector<int> leafs(n), seen(n);
        dfs(al, 0, leafs, seen);

        seen = vector<int>(n);
        return dfs2(al, seats, 0, leafs, seen);
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minimumFuelCost(vector<vector<int>>() = {{0, 1}, {1, 2}}, 3);
    cout << r << endl;

    r = sol.minimumFuelCost(vector<vector<int>>() = {{3, 1}, {3, 2}, {1, 0}, {0, 4}, {0, 5}, {4, 6}}, 2);
    cout << r << endl;
}