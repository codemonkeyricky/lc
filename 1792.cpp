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
    double maxAverageRatio(vector<vector<int>> &classes, int extraStudents)
    {
        priority_queue<array<double, 3>> q;
        for (auto &c : classes)
        {
            double p = c[0], t = c[1];
            q.push({(p + 1) / (t + 1) - p / t, p, t});
        }

        while (extraStudents)
        {
            auto [r, p, t] = q.top();
            q.pop();
            ++p, ++t;
            q.push({(p + 1) / (t + 1) - p / t, p, t});
            --extraStudents;
        }

        double rv = 0;
        while (q.size())
        {
            auto [r, p, t] = q.top();
            q.pop();
            rv += p / t;
        }
        return rv / classes.size();
    }
};

int main()
{
    Solution sol;
    double r;

    r = sol.maxAverageRatio(vector<vector<int>>() = {{2, 4}, {3, 9}, {4, 5}, {2, 10}}, 4);
    cout << r << endl;

    r = sol.maxAverageRatio(vector<vector<int>>() = {{1, 2}, {3, 5}, {2, 2}}, 2);
    cout << r << endl;
}