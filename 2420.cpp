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
    vector<int> goodIndices(vector<int> &nums, int k)
    {
        int n = nums.size();
        vector<int> before(n), after(n);
        for (auto i = 1, k = 1; i < n; ++i)
        {
            before[i] = k;
            k += nums[i - 1] >= nums[i] ? 1 : -k + 1;
        }

        for (int i = n - 2, k = 1; i >= 0; --i)
        {
            after[i] = k;
            k += nums[i] <= nums[i + 1] ? 1 : -k + 1;
        }

        vector<int> rv;
        for (auto i = 0; i < n; ++i)
            if (before[i] >= k && after[i] >= k)
                rv.push_back(i);
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    sol.goodIndices(vector<int>() = {2, 1, 1, 1, 3, 4, 1}, 2);
}