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
    long long maximumSumScore(vector<int> &nums)
    {
        auto r = accumulate(begin(nums), end(nums), 0LL);
        long long l = 0, rv = -1e9;
        for (auto i = 0; i < nums.size(); ++i)
            l += nums[i], rv = max({rv, l, r}), r -= nums[i];
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.maximumSumScore(vector<int>() = {-3, -5});
    cout << r << endl;
}