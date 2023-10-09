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
    int minSizeSubarray(vector<int> &nums, long target)
    {
        long n = nums.size();

        auto nums2 = nums;
        nums.insert(nums.end(), nums2.begin(), nums2.end());

        long rv = 1e9;
        long sum = 0;
        for (long i = 0, j = 0; j < nums.size(); ++j)
        {
            sum += nums[j];
            while (sum > target)
                sum -= nums[i++];
            if (sum == target)
                rv = min(rv, (long)j - i + 1);
        }

        long rv3 = rv;

        rv = 1e9;
        sum = accumulate(begin(nums2), end(nums2), 0ll);
        long rv2 = target / sum * n;

        target %= sum;

        sum = 0;
        for (auto i = 0, j = 0; j < nums.size(); ++j)
        {
            sum += nums[j];
            while (sum > target)
                sum -= nums[i++];
            if (sum == target && (i <= n || j >= n - 2))
                rv = min(rv, (long)j - i + 1);
        }

        rv = min(rv3, rv + rv2);
        return rv >= 1e9 ? -1 : rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minSizeSubarray(vector<int>() = {5, 5, 4, 1, 2, 2, 2, 3, 2, 4, 2, 5}, 56);
    cout << r << endl;

    r = sol.minSizeSubarray(vector<int>() = {1, 2, 2, 2, 1, 2, 1, 2, 1, 2, 1}, 83);
    cout << r << endl;

    r = sol.minSizeSubarray(vector<int>() = {2, 1, 5, 7, 7, 1, 6, 3}, 39);
    cout << r << endl;

    r = sol.minSizeSubarray(vector<int>() = {2, 4, 6, 8}, 3);
    cout << r << endl;

    r = sol.minSizeSubarray(vector<int>() = {1, 1, 1, 2, 3}, 4);
    cout << r << endl;

    r = sol.minSizeSubarray(vector<int>() = {1, 2, 3}, 5);
    cout << r << endl;
}