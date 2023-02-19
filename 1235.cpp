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
    using vi = vector<int>;

public:
    int jobScheduling(vector<int> &start_time, vector<int> &end_time, vector<int> &profit)
    {
        vector<array<int, 3>> jobs = {{0, 0, 0}};
        for (auto i = 0; i < profit.size(); ++i)
            jobs.push_back({end_time[i], start_time[i], profit[i]});

        sort(begin(jobs), end(jobs));
        int n = jobs.size();
        vi dp(n);
        for (auto i = 0; i < n; ++i)
        {
            dp[i] = i ? dp[i - 1] : 0;
            array<int, 3> look = {jobs[i][1] + 1, 0, 0};
            auto it = upper_bound(begin(jobs), end(jobs), look);
            dp[i] = max(jobs[i][2] + dp[--it - begin(jobs)], dp[i]);
        }

        int rv = 0;
        for (auto i = 0; i < n; ++i)
            rv = max(rv, dp[i]);

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.jobScheduling(vector<int>() = {1, 2, 3, 3}, vector<int>() = {3, 4, 5, 6}, vector<int>() = {50, 10, 40, 70});
    cout << r << endl;
}