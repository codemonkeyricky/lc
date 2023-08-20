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
    int countCompleteComponents(int n, vector<vector<int>> &edges)
    {
        parents = vector<int>(n, -1);
        for (auto &e : edges)
        {
            auto p1 = find(e[0]);
            auto p2 = find(e[1]);
            if (p1 != p2)
            {
                if (parents[p1] > parents[p2])
                    swap(p1, p2);
                parents[p1] += parents[p2];
                parents[p2] = p1;
            }
        }

        unordered_map<int, int> cnt;
        set<int> seen;
        for (auto &e : edges)
            ++cnt[find(e[0])], seen.insert(e[0]), seen.insert(e[1]);

        for (auto i = 0; i < n; ++i)
            if (!seen.count(i) && !cnt.count(i))
                cnt[i] = 0;

        int rv = 0;
        for (auto &c : cnt)
        {
            auto v = -parents[c.first];
            auto e = c.second;

            if (v * (v - 1) / 2 == e)
                ++rv;
        }

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.countCompleteComponents(6, vector<vector<int>>() = {{0, 1}, {0, 2}, {1, 2}, {3, 4}});
    cout << r << endl;
}