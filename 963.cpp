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
    size_t d2(int x1, int y1, int x2, int y2)
    {
        return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
    }

public:
    double minAreaFreeRect(vector<vector<int>> &ps, size_t res = 0)
    {
        unordered_map<size_t, vector<vector<int>>> m;
        for (auto i = 0; i < ps.size(); ++i)
            for (auto j = i + 1; j < ps.size(); ++j)
            {
                auto center = ((size_t)(ps[i][0] + ps[j][0]) << 16) + ps[i][1] + ps[j][1];
                m[center].push_back({ps[i][0], ps[i][1], ps[j][0], ps[j][1]});
            }

        for (auto it = begin(m); it != end(m); ++it)
            for (auto i = 0; i < it->second.size(); ++i)
                for (auto j = i + 1; j < it->second.size(); ++j)
                {
                    auto &p1 = it->second[i], &p2 = it->second[j];
                    if ((p1[0] - p2[0]) * (p1[0] - p2[2]) + (p1[1] - p2[1]) * (p1[1] - p2[3]) == 0)
                    {
                        auto area = d2(p1[0], p1[1], p2[0], p2[1]) * d2(p1[0], p1[1], p2[2], p2[3]);
                        if (res == 0 || res > area)
                            res = area;
                    }
                }
        return sqrt(res);
    }
};

int main()
{
    Solution sol;
    double r;

    r = sol.minAreaFreeRect(vector<vector<int>>() = {{1, 2}, {2, 1}, {1, 0}, {0, 1}});
    cout << r << endl;
}