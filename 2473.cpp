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
public:
    vector<long long> minCost(int n, vector<vector<int>> &roads, vector<int> &appleCost, int k)
    {
        vector<vector<array<int, 2>>> al(n + 1);
        for (auto &road : roads)
            al[road[0]].push_back({road[1], road[2]}), al[road[1]].push_back({road[0], road[2]});

        vector<long long> rv;
        for (auto i = 1; i <= n; ++i)
        {
            vector<long long> dist(n + 1, 1e12);
            priority_queue<array<long long, 2>> q;
            q.push({0, i});
            long long r = appleCost[i - 1];
            while (q.size())
            {
                auto [cost, kk] = q.top();
                q.pop();

                r = min(r, (-cost) * (k + 1) + appleCost[kk - 1]);

                for (auto &[n, c] : al[kk])
                    if (-cost + c < dist[n])
                        dist[n] = -cost + c, q.push({cost - c, n});
            }

            rv.push_back(r);
        }

        return rv;
    }
};

int main()
{
    Solution sol;
    vector<long long> r;

    r = sol.minCost(4, vector<vector<int>>() = {{1, 2, 4}, {2, 3, 2}, {2, 4, 5}, {3, 4, 1}, {1, 3, 4}}, vector<int>() = {56, 42, 102, 301}, 2);
    for (auto &c : r)
        cout << c << ", ";
    cout << endl;
}