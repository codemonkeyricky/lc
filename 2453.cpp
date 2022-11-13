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
    int destroyTargets(vector<int> &nums, int space)
    {
        int n = nums.size();
        sort(begin(nums), end(nums));

        unordered_map<int, int> dp;
        for (auto &n : nums)
            ++dp[n % space];

        int mmax = 0, rv = 0;
        for (auto &n : nums)
            if (dp[n % space] > mmax)
                mmax = dp[n % space], rv = n;

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    // r = sol.destroyTargets(vector<int>() = {625879766, 235326233, 250224393, 501422042, 683823101, 948619719, 680305710, 733191937, 182186779, 353350082}, 4);
    // cout << r << endl;

    r = sol.destroyTargets(vector<int>() = {3, 7, 8, 1, 1, 5}, 2);
    cout << r << endl;
}