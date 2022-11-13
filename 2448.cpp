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
    long long minCost(vector<int> &nums, vector<int> &cost)
    {
        int n = nums.size();
        vector<array<long long, 2>> array;
        for (auto i = 0; i < n; ++i)
            array.push_back({nums[i], cost[i]});

        sort(begin(array), end(array));

        vector<long long> right(n);
        long long cost_b = 0;
        for (int i = n - 2; i >= 0; --i)
        {
            right[i] = right[i + 1];
            right[i] += (array[i + 1][0] - array[i][0]) * (array[i + 1][1] + cost_b);
            cost_b += array[i + 1][1];
        }

        long long rv = right[0];
        long long left = 0, cost_a = 0;
        for (auto i = 0; i < n - 1; ++i)
        {
            left += (array[i + 1][0] - array[i][0]) * (array[i][1] + cost_a);
            cost_a += array[i][1];
            rv = min(rv, left + (i < n - 1 ? right[i + 1] : 0));
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    long long r;

    r = sol.minCost(vector<int>() = {735103, 366367, 132236, 133334, 808160, 113001, 49051, 735598, 686615, 665317, 999793, 426087, 587000, 649989, 509946, 743518}, vector<int>() = {724182, 447415, 723725, 902336, 600863, 287644, 13836, 665183, 448859, 917248, 397790, 898215, 790754, 320604, 468575, 825614});
    cout << r << endl;

    // r = sol.minCost(vector<int>() = {2, 2, 2, 2, 2}, vector<int>() = {4, 2, 8, 1, 3});
    // cout << r << endl;

    r = sol.minCost(vector<int>() = {1, 3, 5, 2}, vector<int>() = {2, 3, 1, 14});
    cout << r << endl;
}