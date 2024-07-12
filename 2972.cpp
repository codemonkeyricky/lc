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
    long long incremovableSubarrayCount(vector<int> &nums)
    {
        long long rv = 0;
        int n = nums.size();
        map<int, int> lookup;
        for (int i = n - 1; i >= 0 && (i == n - 1 || nums[i] < nums[i + 1]); --i)
            lookup[nums[i]] = i, ++rv;

        int remove_all = 0;
        if (lookup.size() == n)
            ++remove_all;

        for (auto i = 0; i < n - 1 && (i == 0 || nums[i - 1] < nums[i]); ++i)
        {
            auto it = lookup.upper_bound(nums[i]);
            if (it != lookup.end())
            {
                if (it->second - i > 1)
                    ++rv;
                rv += n - it->second;
            }
            else
                ++rv;
        }

        return rv + !remove_all;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.incremovableSubarrayCount(vector<int>() = {1, 2, 10, 6});
    cout << r << endl;

    r = sol.incremovableSubarrayCount(vector<int>() = {6, 5, 7, 8});
    cout << r << endl;

    r = sol.incremovableSubarrayCount(vector<int>() = {1, 2, 3, 4});
    cout << r << endl;
}