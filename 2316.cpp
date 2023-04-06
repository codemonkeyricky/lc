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
    vector<int> parents;

    int find(int k)
    {
        if (parents[k] < 0)
            return k;
        return parents[k] = find(parents[k]);
    }

public:
    long long countPairs(int n, vector<vector<int>> &edges)
    {
        parents = vector<int>(n, -1);
        for (auto &e : edges)
        {
            auto a = e[0], b = e[1];
            auto p1 = find(a);
            auto p2 = find(b);
            if (p1 != p2)
            {
                if (p1 > p2)
                    swap(p1, p2);
                parents[p1] += parents[p2];
                parents[p2] = p1;
            }
        }

        unordered_map<int, int> dp;
        for (auto i = 0; i < n; ++i)
        {
            auto p = find(i);
            dp[p] = abs(parents[p]);
        }

        long long rv = (long long)n * (n - 1) / 2;
        for (auto &d : dp)
        {
            auto k = d.second;
            rv -= (long long)k * (k - 1) / 2;
        }

        return rv; 
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.countPairs(7, vector<vector<int>>() = {{0, 2}, {0, 5}, {2, 4}, {1, 6}, {5, 4}});
    cout << r << endl;
}