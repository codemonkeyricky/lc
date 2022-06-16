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
    int maximumUniqueSubarray(vector<int> &nums)
    {
        auto psum = nums;
        partial_sum(begin(psum), end(psum), begin(psum));
        int rv = 0;
        unordered_map<int, int> dp;
        int k = -1;
        for (auto i = 0; i < psum.size(); ++i)
        {
            if (dp.count(nums[i]))
                k = max(k, dp[nums[i]]);
            dp[nums[i]] = i;
            rv = max(rv, psum[i] - ((k == -1) ? 0 : psum[k]));
        }
        
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}