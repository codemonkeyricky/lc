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
    int minAbsoluteDifference(vector<int> &nums, int x)
    {
        multiset<long> set = {(int)-2e9, (int)2e9};
        int n = nums.size();
        for (int i = n - 1; i >= x ; --i)
            set.insert(nums[i]);

        long rv = 1e9;
        for (auto i = 0; i + x  < n; ++i)
        {
            auto n = set.lower_bound(nums[i]);
            auto p = prev(n);
            rv = min({rv, abs(*n - nums[i]), abs(*p - nums[i])});
            set.erase(set.find(nums[i + x]));
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    // r = sol.minAbsoluteDifference(vector<int>() = {1, 2, 3, 4}, 3);
    // cout << r << endl;

    r = sol.minAbsoluteDifference(vector<int>() = {4, 3, 2, 4}, 2);
    cout << r << endl;
}