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
    long long countInterestingSubarrays(vector<int> &nums, int mod, int k)
    {
        int n = nums.size();
        unordered_map<int, int> dp;

        int kk = 0;
        dp[0] = 1;
        long long rv = 0;
        for (auto i = 0; i < n; ++i)
        {
            if ((nums[i] % mod) == k)
                kk = (kk + 1) % mod;
            rv += dp[(kk - k + mod) % mod];
            ++dp[kk];
        }

        return rv;
    }

};

int main()
{
    Solution sol;
    int r;

    // r = sol.countInterestingSubarrays(vector<int>() = {11, 12, 21, 31}, 10, 1);
    // cout << r << endl;

    r = sol.countInterestingSubarrays(vector<int>() = {3, 1, 9, 6}, 3, 0);
    cout << r << endl;

    r = sol.countInterestingSubarrays(vector<int>() = {3, 2, 4}, 2, 1);
    cout << r << endl;
}