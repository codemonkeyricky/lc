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
    int countSubarrays(vector<int> &nums, int k)
    {
        int kk = -1, n = nums.size();
        for (auto i = 0; i < n && kk == -1; ++i)
            if (nums[i] == k)
                kk = i;

        int sum = 0;
        unordered_map<int, int> rightEven, rightOdd;
        for (int i = kk + 1; i < n; ++i)
        {
            sum += nums[i] < k ? -1 : 1;
            if ((i - kk) % 2)
                ++rightOdd[sum];
            else
                ++rightEven[sum];
        }

        vector<int> left(n);
        sum = 0;
        int rv = 0;
        for (int i = kk - 1; i >= 0; --i)
        {
            sum += nums[i] < k ? -1 : 1;
            if ((kk - i) % 2) // odd
                rv += rightOdd[-sum] + rightEven[-sum + 1];
            else
                rv += rightEven[-sum] + rightOdd[-sum + 1];
        }

        // kk on edge
        ++rv; 
        sum = 0;
        for (int i = kk - 1; i >= 0; --i)
        {
            sum += nums[i] < k ? -1 : 1;
            if ((kk - i) % 2) // odd
                rv += sum == 1;
            else
                rv += sum == 0;
        }

        sum = 0;
        for (int i = kk + 1; i < n; ++i)
        {
            sum += nums[i] < k ? -1 : 1;
            if ((kk - i) % 2) // odd
                rv += sum == 1;
            else
                rv += sum == 0;
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    // r = sol.countSubarrays(vector<int>() = {2, 5, 1, 4, 3, 6}, 1);
    // cout << r << endl;

    r = sol.countSubarrays(vector<int>() = {2, 3, 1}, 3);
    cout << r << endl;

    r = sol.countSubarrays(vector<int>() = {3, 2, 1, 4, 5}, 4);
    cout << r << endl;
}