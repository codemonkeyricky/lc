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
    bool canBeIncreasing(vector<int> &nums)
    {
        if (nums.size() <= 2)
            return true;

        int n = nums.size();
        vector<int> maxSoFar(n), minSoFar(n, 1e9);
        for (auto i = 0; i < n; ++i)
            maxSoFar[i] = max(nums[i], i ? maxSoFar[i - 1] : 0);

        for (int i = n - 1; i >= 0; --i)
            minSoFar[i] = min(nums[i], i < n - 1 ? minSoFar[i + 1] : (int)1e9);

        for (auto i = 1; i < n - 1; ++i)
            if (maxSoFar[i - 1] < minSoFar[i + 1])
                return true;

        int valid = true;
        for (auto i = 1; i < n - 1; ++i)
            if (nums[i] >= nums[i + 1])
                valid = false;
        if (valid)
            return true;

        valid = true;
        for (auto i = 0; i < n - 2; ++i)
            if (nums[i] >= nums[i + 1])
                valid = false;

        return valid;
    }
};

int main()
{
    Solution sol;
    int r;

    // r = sol.canBeIncreasing(vector<int>() = {541, 783, 433, 744});
    // cout << r << endl;

    r = sol.canBeIncreasing(vector<int>() = {1, 2, 10, 5, 7});
    cout << r << endl;
}