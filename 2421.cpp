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
    int find(vector<int> &parents, int k)
    {
        if (parents[k] < 0)
            return k;
        return parents[k] = find(parents, parents[k]);
    }

    void unionize(vector<int> &vals, vector<int> &parents, int i, int j)
    {
        auto p1 = find(parents, i);
        auto p2 = find(parents, j);
        if (vals[p1] < vals[p2])
            swap(p1, p2);

        parents[p2] = p1;
        if (vals[p2] == vals[p1])
            --parents[p1];
    }

public:
    int numberOfGoodPaths(vector<int> &vals, vector<vector<int>> &edges)
    {
        int n = vals.size();
        vector<array<int, 2>> vvals;
        for (auto i = 0; i < n; ++i)
            vvals.push_back({vals[i], i});

        sort(begin(vvals), end(vvals));

        vector<vector<int>> al(n);
        for (auto &e : edges)
            al[e[0]].push_back(e[1]), al[e[1]].push_back(e[0]);

        int rv = 0;
        vector<int> parents(n, -1);
        unordered_set<int> permit;
        for (auto [v, k] : vvals)
        {
            for (auto &n : al[k])
                if (vals[n] <= v && permit.count(n))
                    if (find(parents, n) != find(parents, k))
                        unionize(vals, parents, n, k);

            rv += abs(parents[find(parents, k)]);
            permit.insert(k);
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.numberOfGoodPaths(vector<int>() = {1, 1, 2, 2, 3}, vector<vector<int>>() = {{0, 1}, {1, 2}, {2, 3}, {2, 4}});
    cout << r << endl;

    r = sol.numberOfGoodPaths(vector<int>() = {1, 3, 2, 1, 3}, vector<vector<int>>() = {{0, 1}, {0, 2}, {2, 3}, {2, 4}});
    cout << r << endl;
}