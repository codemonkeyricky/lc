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
    int visiblePoints(vector<vector<int>> &points, int angle, vector<int> &loc)
    {
        vector<double> angles;
        double theta = angle * M_PI / 180;
        int k = 0;
        for (auto &p : points)
            if (p[0] == loc[0] && p[1] == loc[1])
                ++k;
            else
                angles.push_back(atan2(p[1] - loc[1], p[0] - loc[0]));
        sort(begin(angles), end(angles));

        int rv = 0, n = angles.size();
        for (auto i = 0, j = 0; j < n * 2; ++j)
        {
            while ((j >= n ? 2 * M_PI : 0) + angles[j % n] - (angles[i % n] + (i >= n ? 2 * M_PI : 0)) > theta)
                ++i;
            rv = max(rv, j - i + 1);
        }
        return rv + k;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.visiblePoints(vector<vector<int>>() = {{45, 26}, {82, 12}, {33, 83}, {58, 50}, {55, 92}, {66, 42}, {25, 74}, {74, 74}, {36, 87}, {7, 41}, {89, 36}, {44, 22}, {84, 9}, {96, 90}, {75, 51}, {87, 15}, {50, 75}, {90, 84}, {56, 18}, {43, 48}, {23, 27}, {100, 34}}, 12, vector<int>() = {32, 37});
    cout << r << endl;

    r = sol.visiblePoints(vector<vector<int>>() = {{0, 0}, {0, 2}}, 90, vector<int>() = {1, 1});
    cout << r << endl;

    r = sol.visiblePoints(vector<vector<int>>() = {{1, 1}, {2, 2}, {1, 2}, {2, 1}}, 0, vector<int>() = {1, 1});
    cout << r << endl;

    r = sol.visiblePoints(vector<vector<int>>() = {{2, 1}, {2, 2}, {3, 3}}, 90, vector<int>() = {1, 1});
    cout << r << endl;
}