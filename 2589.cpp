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
    int findMinimumTime(vector<vector<int>> &tasks)
    {
        vector<vector<int>> tasks2;
        for (auto &t : tasks)
            tasks2.push_back({t[1], t[0], t[2]});
        sort(begin(tasks2), end(tasks2));
        swap(tasks2, tasks);

        vector<int> on(tasks.back()[0] + 1);

        int n = tasks.size();
        for (auto i = 0; i < n; ++i)
        {
            int duration = tasks[i][2];
            int k = tasks[i][0];
            for (auto j = tasks[i][1]; duration && j <= tasks[i][0]; ++j)
                if (on[j])
                    --duration;

            while (duration)
            {
                if (!on[k])
                    on[k] = 1, --duration;
                --k;
            }
        }

        return accumulate(begin(on), end(on), 0);
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.findMinimumTime(vector<vector<int>>() = {{1, 16, 3}, {10, 20, 5}, {1, 12, 4}, {8, 11, 2}});
    cout << r << endl;

    r = sol.findMinimumTime(vector<vector<int>>() = {{1, 18, 5}, {3, 15, 1}});
    cout << r << endl;

    r = sol.findMinimumTime(vector<vector<int>>() = {{1, 3, 2}, {2, 5, 3}, {5, 6, 2}});
    cout << r << endl;

    r = sol.findMinimumTime(vector<vector<int>>() = {{2, 3, 1}, {4, 5, 1}, {1, 5, 2}});
    cout << r << endl;
}