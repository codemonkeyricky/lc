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

using v = vector<int>;
class Solution
{
    long long count(vector<int> &nums, int i, int j, int minK, int maxK)
    {
        v mmin, mmax;
        for (auto k = i; k < j; ++k)
        {
            if (nums[k] == minK)
                mmin.push_back(k);
            if (nums[k] == maxK)
                mmax.push_back(k);
        }

        if (mmin.size() == 0 || mmax.size() == 0)
            return 0;

        long long rv = 0;
        int ii = i, jj = j;
        i = j = 0;
        while (i < mmin.size() && j < mmax.size())
        {
            if (mmin[i] <= mmax[j])
                rv += (mmin[i] - ii + 1) * (jj - mmax[j]);
            else
                rv += (mmax[j] - ii + 1) * (jj - mmin[i]);

            if(mmin[i] < mmax[j])
                ii = mmin[i] + 1, ++i;
            else if (mmin[i] > mmax[j])
                ii = mmax[j] + 1, ++j;
            else
                ii = mmin[i] + 1, ++i, ++j;
        }
        return rv;
    }

public:
    long long countSubarrays(vector<int> &nums, int minK, int maxK)
    {
        int n = nums.size();
        long long rv = 0;
        for (auto i = 0, j = 0; i < n; ++j, i = j)
        {
            while (j < n && minK <= nums[j] && nums[j] <= maxK)
                ++j;
            rv += count(nums, i, j, minK, maxK);
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    // r = sol.countSubarrays(v() = {35054, 398719, 945315, 945315, 820417, 945315, 35054, 945315, 171832, 945315, 35054, 109750, 790964, 441974, 552913}, 35054, 945315);
    // cout << r << endl;

    r = sol.countSubarrays(v() = {1, 2, 3, 2, 1}, 1, 3);
    cout << r << endl;

    r = sol.countSubarrays(v() = {1, 1, 1, 1}, 1, 1);
    cout << r << endl;

    r = sol.countSubarrays(v() = {1, 3, 5, 2, 7, 5}, 1, 5);
    cout << r << endl;
}