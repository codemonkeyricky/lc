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
    array<priority_queue<int>, 2> dfs(vector<int> &cost, vector<vector<int>> &al, int p, int u, vector<long long> &rv)
    {
        priority_queue<int> pq, nq;
        for (auto &v : al[u])
            if (v != p)
            {
                auto [pqq, nqq] = dfs(cost, al, u, v, rv);
                while (pqq.size())
                    pq.push(pqq.top()), pqq.pop();
                while (nqq.size())
                    nq.push(nqq.top()), nqq.pop();
            }

        if (cost[u] > 0)
            pq.push(-cost[u]);
        else 
            nq.push(cost[u]);

        while (pq.size() > 3)
            pq.pop();
        while (nq.size() > 3)
            nq.pop();

        if (pq.size() + nq.size() >= 3)
        {
            vector<long long> a, b;
            while (pq.size())
                a.push_back(-pq.top()), pq.pop();
            reverse(begin(a), end(a));
            while (a.size() < 3)
                a.push_back(0);

            while (nq.size())
                b.push_back(nq.top()), nq.pop();
            reverse(begin(b), end(b));
            while (b.size() < 3)
                b.push_back(0);

            long long x, y;
            x = a[0] * a[1] * a[2];
            y = b[0] * b[1] * a[0];

            rv[u] = max(x, y);
            for (auto &aa : a)
                if (aa)
                    pq.push(-aa);
            for (auto &bb : b)
                if (bb)
                    nq.push(bb);
        }

        return {pq, nq};
    }

public:
    vector<long long> placedCoins(vector<vector<int>> &edges, vector<int> &cost)
    {
        int n = cost.size();

        vector<vector<int>> al(n);
        for (auto &e : edges)
            al[e[0]].push_back(e[1]),
                al[e[1]].push_back(e[0]);

        vector<long long> rv(n, 1);
        dfs(cost, al, -1, 0, rv);
        return rv;
    }
};

int main()
{
    Solution sol;
    vector<long long> r;

    r = sol.placedCoins(vector<vector<int>>() = {{0, 8}, {8, 1}, {9, 2}, {4, 6}, {7, 4}, {3, 7}, {3, 8}, {5, 8}, {5, 9}}, vector<int>() = {-4, 83, -97, 40, 86, -85, -6, -84, -16, -53});
    for (auto &rr : r)
        cout << rr << ", ";
    cout << endl;

    r = sol.placedCoins(vector<vector<int>>() = {{0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {0, 7}, {0, 8}, {0, 9}, {0, 10}, {0, 11}, {0, 12}, {0, 13}, {0, 14}, {0, 15}, {0, 16}, {0, 17}, {0, 18}, {0, 19}, {0, 20}, {0, 21}, {0, 22}, {0, 23}, {0, 24}, {0, 25}, {0, 26}, {0, 27}, {0, 28}, {0, 29}, {0, 30}, {0, 31}, {0, 32}, {0, 33}, {0, 34}, {0, 35}, {0, 36}, {0, 37}, {0, 38}, {0, 39}, {0, 40}, {0, 41}, {0, 42}, {0, 43}, {0, 44}, {0, 45}, {0, 46}, {0, 47}, {0, 48}, {0, 49}, {0, 50}, {0, 51}, {0, 52}, {0, 53}, {0, 54}, {0, 55}, {0, 56}, {0, 57}, {0, 58}, {0, 59}, {0, 60}, {0, 61}, {0, 62}, {0, 63}, {0, 64}, {0, 65}, {0, 66}, {0, 67}, {0, 68}, {0, 69}, {0, 70}, {0, 71}, {0, 72}, {0, 73}, {0, 74}, {0, 75}, {0, 76}, {0, 77}, {0, 78}, {0, 79}, {0, 80}, {0, 81}, {0, 82}, {0, 83}, {0, 84}, {0, 85}, {0, 86}, {0, 87}, {0, 88}, {0, 89}, {0, 90}, {0, 91}, {0, 92}, {0, 93}, {0, 94}, {0, 95}, {0, 96}, {0, 97}, {0, 98}, {0, 99}}, vector<int>() = {-5959, 602, -6457, 7055, -1462, 6347, 7226, -8422, -6088, 2997, -7909, 6433, 5217, 3294, -3792, 7463, 8538, -3811, 5009, 151, 5659, 4458, -1702, -1877, 2799, 9861, -9668, -1765, 2181, -8128, 7046, 9529, 6202, -8026, 6464, 1345, 121, 1922, 7274, -1227, -9914, 3025, 1046, -9368, -7368, 6205, -6342, 8091, -6732, -7620, 3276, 5136, 6871, 4823, -1885, -4005, -3974, -2725, -3845, -8508, 7201, -9566, -7236, -3386, 4021, 6793, -8759, 5066, 5879, -5171, 1011, 1242, 8536, -8405, -9646, -214, 2251, -9934, -8820, 6206, 1006, 1318, -9712, 7230, 5608, -4601, 9185, 346, 3056, 8913, -2454, -3445, -4295, 4802, -8852, -6121, -4538, -5580, -9246, -6462});
    for (auto &rr : r)
        cout << rr << ", ";
    cout << endl;

    r = sol.placedCoins(vector<vector<int>>() = {{0, 1}, {0, 2}}, vector<int>() = {1, 2, -2});
    for (auto &rr : r)
        cout << rr << ", ";
    cout << endl;

    r = sol.placedCoins(vector<vector<int>>() = {{0, 1}, {0, 2}, {1, 3}, {1, 4}, {1, 5}, {2, 6}, {2, 7}, {2, 8}}, vector<int>() = {1, 4, 2, 3, 5, 7, 8, -4, 2});
    for (auto &rr : r)
        cout << rr << ", ";
    cout << endl;

    r = sol.placedCoins(vector<vector<int>>() = {{0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}}, vector<int>() = {1, 2, 3, 4, 5, 6});
    for (auto &rr : r)
        cout << rr << ", ";
    cout << endl;
}