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
    long long cal(int n)
    {
        vector<long long> f(n + 2);
        f[0] = 1;
        f[1] = 2;
        for (int i = 2; i <= n; i++)
            f[i] = f[i - 1] + f[i - 2];
        return f[n];
    }

    int seen[1001] = {};

    void dfs(vector<int> &nums, int c, int k, vector<int> &group)
    {
        seen[c] = true;
        group.push_back(c);
        auto it = lower_bound(begin(nums), end(nums), c + k);
        if (it != end(nums) && *it == c + k)
            dfs(nums, c + k, k, group);
    }

public:
    long long countTheNumOfKFreeSubsets(vector<int> &nums, int k)
    {
        // Split into groups
        sort(begin(nums), end(nums));
        vector<vector<int>> groups;
        for (auto &c : nums)
        {
            vector<int> group;
            if (!seen[c])
                dfs(nums, c, k, group);
            groups.push_back(group);
        }

        long long rv = 1;
        for (auto &vec : groups)
            rv = rv * cal(vec.size());

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    // r = sol.countTheNumOfKFreeSubsets(vector<int>() = {483, 482, 486, 481, 485}, 2);
    // cout << r << endl;

    // r = sol.countTheNumOfKFreeSubsets(vector<int>() = {7, 8, 9, 14, 11, 6, 10, 13, 12}, 6);
    // cout << r << endl;

    // r = sol.countTheNumOfKFreeSubsets(vector<int>() = {2, 3, 5, 8}, 5);
    // cout << r << endl;

    r = sol.countTheNumOfKFreeSubsets(vector<int>() = {5, 4, 6}, 1);
    cout << r << endl;
}