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
    int numberOfBoomerangs(vector<vector<int>> &points, int rv = 0)
    {
        int n = points.size();
        unordered_map<int, int> dp;
        for (auto i = 0; i < n; ++i, dp.clear())
        {
            for (auto j = 0; j < n; ++j)
                if (i != j)
                    ++dp[(points[i][0] - points[j][0]) * (points[i][0] - points[j][0]) + (points[i][1] - points[j][1]) * (points[i][1] - points[j][1])];

            for (auto &d : dp)
                if (d.second >= 2)
                    rv += d.second * (d.second - 1);
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.numberOfBoomerangs(vector<vector<int>>() = {{0, 0}, {1, 0}, {2, 0}});
    cout << r << endl;
}