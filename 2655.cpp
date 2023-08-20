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
    vector<vector<int>> findMaximalUncoveredRanges(int n, vector<vector<int>> &ranges)
    {
        map<int, int> intervals;
        for (auto &r : ranges)
            ++intervals[r[0]], --intervals[r[1]];

        int sum = 0, last = -1;
        vector<vector<int>> rv;

        if (intervals.empty())
            return {{0, n - 1}};

        if (intervals.begin()->first > 0)
            rv.push_back({0, intervals.begin()->first - 1});

        for (auto &v : intervals)
        {
            sum += v.second;
            if (last != -1)
            {
                if (v.first - last > 1)
                    rv.push_back({last + 1, v.first - 1});
                last = -1;
            }

            if (sum == 0)
                last = v.first;
        }

        if (n - 1 - prev(intervals.end())->first)
            rv.push_back({prev(intervals.end())->first + 1, n - 1});

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    sol.findMaximalUncoveredRanges(10, vector<vector<int>>() = {{0, 0}, {6, 6}, {0, 2}, {9, 9}});

    sol.findMaximalUncoveredRanges(3, vector<vector<int>>() = {{0, 2}});
    cout << r << endl;
}