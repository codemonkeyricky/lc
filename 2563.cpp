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
    long long countFairPairs(vector<int> &nums, int lower, int upper)
    {
        sort(begin(nums), end(nums));
        long long rv = 0;
        for (auto i = 0; i < nums.size(); ++i)
        {
            auto l = lower_bound(begin(nums) + i, end(nums), lower - nums[i]);
            auto h = upper_bound(begin(nums) + i, end(nums), upper - nums[i]);
            if (h - l > 0)
                rv += h - l - (*l == nums[i] ? 1 : 0);
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    // r = sol.countFairPairs(vector<int>() = {0, 0, 0, 0, 0, 0}, 0, 0);
    // cout << r << endl;

    // r = sol.countFairPairs(vector<int>() = {1, 7, 9, 2, 5}, 11, 11);
    // cout << r << endl;

    r = sol.countFairPairs(vector<int>() = {0, 1, 7, 4, 4, 5}, 3, 6);
    cout << r << endl;
}