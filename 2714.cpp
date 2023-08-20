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
    int shortestPathWithHops(int n, vector<vector<int>> &edges, int s, int d, int k)
    {
        vector<unordered_map<int, int>> al(n);
        for(auto & e : edges)
            al[e[0]][e[1]] = al[e[1]][e[0]] = e[2];

        vector<vector<int>> seen(n, vector<int>(k + 1, 1e9));
        priority_queue<array<int, 3>> q; // weight / node / free remaining
        q.push({0, s, k});
        seen[s][k] = 0;
        int rv = 1e9;
        while (q.size())
        {
            auto [w, u, k] = q.top();
            q.pop();

            if (u == d)
                rv = min(rv, -w);
            else
                for (auto [v, ww] : al[u])
                {
                    if (-(w - ww) < seen[v][k])
                        q.push({w - ww, v, k}), seen[v][k] = -(w - ww);
                    if (k && -w < seen[v][k - 1])
                        q.push({w, v, k - 1}), seen[v][k - 1] = -w;
                }

        }

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.shortestPathWithHops(15, vector<vector<int>>() = {{0, 6, 350607}, {5, 6, 448412}, {4, 5, 203629}, {1, 4, 201710}, {2, 6, 760400}, {3, 1, 826303}, {1, 2, 909770}, {4, 6, 572569}, {3, 5, 302032}, {2, 4, 841593}, {0, 2, 232899}, {2, 5, 125128}, {1, 6, 164371}, {0, 1, 335563}, {3, 4, 545341}, {0, 4, 714158}, {0, 3, 647347}, {12, 9, 57452}, {10, 12, 932217}, {11, 10, 203240}, {14, 11, 863408}, {13, 14, 199844}, {8, 13, 942937}, {7, 8, 251139}, {9, 2, 366717}}, 0, 9, 8);
    cout << r << endl;

    r = sol.shortestPathWithHops(7, vector<vector<int>>() = {{3, 1, 9}, {3, 2, 4}, {4, 0, 9}, {0, 5, 6}, {3, 6, 2}, {6, 0, 4}, {1, 2, 4}}, 4, 1, 2);
    cout << r << endl;
}