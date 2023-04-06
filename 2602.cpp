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
    vector<long long> minOperations(vector<int> &nums, vector<int> &queries)
    {
        sort(begin(nums), end(nums));
        vector<array<int, 2>> q;
        for (auto i = 0; i < queries.size(); ++i)
            q.push_back({queries[i], i});

        int n = nums.size();
        vector<long long> pre(n);
        for (int i = 0; i < n; ++i)
            pre[i] = (i ? pre[i - 1] : 0) + nums[i];

        vector<long long> post(n);
        for (int i = n - 1; i >= 0; --i)
            post[i] = ((i + 1 < n) ? post[i + 1] : 0) + nums[i];

        vector<long long> rv;
        for (auto &q : queries)
        {
            long long inc = 0, dec = 0;
            auto k = prev(upper_bound(begin(nums), end(nums), q)) - begin(nums);
            if (k >= 0)
                inc = (k + 1) * q - pre[k];
            if (k + 1 < n)
                dec = post[k + 1] - (n - k - 1) * q;
            rv.push_back(inc + dec);
        }

        return rv;
    }
};

int main()
{
    Solution sol;
    vector<long long> r;

    r = sol.minOperations(vector<int>() = {47, 50, 97, 58, 87, 72, 41, 63, 41, 51, 17, 21, 7, 100, 69, 66, 79, 92, 84, 9, 57, 26, 26, 28, 83, 38}, vector<int>() = {50, 84, 76, 41, 64, 82, 20, 22, 64, 7, 38, 92, 39, 28, 22, 3, 41, 46, 47, 50, 88, 51, 9, 49, 38, 67, 26, 65, 89, 27, 71, 25, 77, 72, 65, 41, 84, 68, 51, 26, 84, 24, 79, 41, 96, 83, 92, 9, 93, 84, 35, 70, 74, 79, 37, 38, 26, 26, 41, 26});
    r = sol.minOperations(vector<int>() = {2, 9, 6, 3}, vector<int>() = {10});
    r = sol.minOperations(vector<int>() = {3, 1, 6, 8}, vector<int>() = {1, 5});
}