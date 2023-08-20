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
    int minimumDistance(int n, vector<vector<int>> &edges, int s, vector<int> &marked)
    {
        vector<set<array<int, 2>>> al(n);
        for (auto &e : edges)
            al[e[0]].insert({e[1], e[2]});

        set<int> mark(begin(marked), end(marked));

        vector<int> dist(n, 1e9);
        priority_queue<array<int, 2>> q;
        q.push({0, s});
        while (q.size())
        {
            auto [d, k] = q.top();
            q.pop();

            if (mark.count(k))
                return dist[k];

            for (auto &[v, w] : al[k])
                if (-d + w < dist[v])
                    dist[v] = -d + w, q.push({d - w, v});
        }

        return -1;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minimumDistance(5, vector<vector<int>>() = {{0, 1, 2}, {0, 2, 4}, {1, 3, 1}, {2, 3, 3}, {3, 4, 2}}, 1, vector<int>() = {0, 4});
    cout << r << endl;

    r = sol.minimumDistance(4, vector<vector<int>>() = {{0, 1, 1}, {1, 2, 3}, {2, 3, 2}, {0, 3, 4}}, 0, vector<int>() = {2, 3});
    cout << r << endl;
}