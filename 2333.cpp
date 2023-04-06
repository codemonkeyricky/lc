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
    array<long long, 2> sdiff(vector<array<int, 2>> &nums, int diff, int k)
    {
        int n = nums.size();
        long long rv = 0;
        for (int i = n - 1; i >= 0; --i)
        {
            auto [a, b] = nums[i];
            long long d = abs(a - b);
            if (d > diff && k)
            {
                long long rm = min(d - diff, (long long)k);
                d -= rm, k -= rm;
            }
            else if (d && k)
                --d, --k;

            rv += d * d;
        }
        return {k, rv};
    }

public:
    long long minSumSquareDiff(vector<int> &nums1, vector<int> &nums2, int k1, int k2)
    {
        int n = nums1.size();
        vector<array<int, 2>> nums;
        for (auto i = 0; i < n; ++i)
            nums.push_back({nums1[i], nums2[i]});

        sort(begin(nums), end(nums), [](const array<int, 2> &l, const array<int, 2> &r)
             { return abs(l[0] - l[1]) < abs(r[0] - r[1]); });

        long long l = 0;
        long long r = 1e9;
        while (l < r)
        {
            long long m = (l + r + 1) / 2;
            auto [k, rv] = sdiff(nums, m, k1 + k2);
            if (k == 0)
                l = m;
            else
                r = m - 1;
        }

        return sdiff(nums, l, k1 + k2)[1];
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minSumSquareDiff(vector<int>() = {7, 11, 4, 19, 11, 5, 6, 1, 8}, vector<int>() = {4, 7, 6, 16, 12, 9, 10, 2, 10}, 3, 6);
    cout << r << endl;

    r = sol.minSumSquareDiff(vector<int>() = {1, 2, 3, 4}, vector<int>() = {2, 10, 20, 19}, 0, 0);
    cout << r << endl;

    r = sol.minSumSquareDiff(vector<int>() = {1, 4, 10, 12}, vector<int>() = {5, 8, 6, 9}, 1, 1);
    cout << r << endl;
}