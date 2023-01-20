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
    long long dfs(vector<set<int>> &al, vector<int> &price, int prev, int curr)
    {
        long long r = 0;
        priority_queue<array<long long, 2>> p;
        for (auto &next : al[curr])
            if (next != prev && !lookup[curr].count(next))
            {
                auto cost = dfs(al, price, curr, next);
                lookup[curr][next] = cost;
                rlookup[curr][cost].insert(next);
            }
        
        long long largest = 0;
        if (rlookup[curr].size() >= 1 &&
            (rbegin(rlookup[curr])->second.size() >= 2 ||
             !rbegin(rlookup[curr])->second.count(prev)))
            largest = rbegin(rlookup[curr])->first;
        else if (rlookup[curr].size() >= 2)
            largest = next(rbegin(rlookup[curr]))->first;

        return largest + price[curr];
    }

    vector<map<int, long long>> lookup;
    vector<map<long long, set<int>>> rlookup;

public:
    long long maxOutput(int n, vector<vector<int>> &edges, vector<int> &price)
    {
        vector<set<int>> al(n);
        for (auto &e : edges)
            al[e[0]].insert(e[1]), al[e[1]].insert(e[0]);

        vector<int> leaves;
        for (auto i = 0; i < n; ++i)
            if (al[i].size() == 1)
                leaves.push_back(i);

        lookup = vector<map<int, long long>>(n);
        rlookup = vector<map<long long, set<int>>>(n);

        long long rv = 0; 
        for (auto &leaf : leaves)
            rv = max(rv, dfs(al, price, -1, leaf) - price[leaf]);

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.maxOutput(7, vector<vector<int>>() = {{0, 1}, {1, 2}, {1, 3}, {1, 5}, {5, 6}, {3, 4}}, vector<int>() = {1, 9, 1, 8, 8, 8, 8});
    cout << r << endl;

    r = sol.maxOutput(9, vector<vector<int>>() = {{1, 7}, {5, 2}, {2, 3}, {6, 0}, {0, 4}, {4, 7}, {7, 3}, {3, 8}}, vector<int>() = {6, 13, 8, 10, 4, 5, 8, 3, 12});
    cout << r << endl;

    r = sol.maxOutput(6, vector<vector<int>>() = {{0, 1}, {1, 2}, {1, 3}, {3, 4}, {3, 5}}, vector<int>() = {9, 8, 7, 6, 10, 5});
    cout << r << endl;
}