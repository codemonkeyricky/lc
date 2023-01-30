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
    void set(vector<int> &bit, int k, int v)
    {
        for (auto i = k + 1; i < 4002; i += i & -i)
            bit[i] += v;
    }

    int get(vector<int> &bit, int k)
    {
        int rv = 0;
        for (auto i = k + 1; i; i -= i & -i)
            rv += bit[i];
        return rv;
    }

public:
    long long countQuadruplets(vector<int> &nums)
    {
        long long n = nums.size(), rv = 0;
        vector<int> pre(4002), post(4002);
        for (auto &n : nums)
            set(post, n, 1);

        for (auto j = 0; j < n; ++j)
        {
            auto ppost = post;
            for (auto k = j; k < n; ++k)
            {
                if (nums[k] < nums[j])
                    rv += (long)get(pre, nums[k]) * (get(ppost, 4000) - get(ppost, nums[j]));
                set(ppost, nums[k], -1);
            }
            set(pre, nums[j], 1);
            set(post, nums[j], -1);
        }

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.countQuadruplets(vector<int>() = {3, 9, 5, 4, 8, 2, 1, 10, 7, 6});
    cout << r << endl;

    r = sol.countQuadruplets(vector<int>() = {1, 2, 3, 4});
    cout << r << endl;

    r = sol.countQuadruplets(vector<int>() = {1, 3, 2, 4, 5});
    cout << r << endl;
}