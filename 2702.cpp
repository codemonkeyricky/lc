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
    int minOperations(vector<int> &nums, int x, int y)
    {
        long long n = nums.size(), l = 1, r = 1e10, d = x - y;
        while (l < r)
        {
            long long m = (l + r) / 2;
            long long op_y = m, op_x = m, i;
            for (i = 0; i < n && op_x >= 0; ++i)
            {
                auto op_x_needed = (max(0ll, (long long)nums[i] - op_y * y) + d - 1) / d;
                op_x -= op_x_needed;
            }

            if (op_x >= 0)
                r = m; // find smaller 
            else
                l = m + 1; // find bigger
        }

        return l;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minOperations(vector<int>() = {1, 2, 1}, 2, 1);
    cout << r << endl;

    r = sol.minOperations(vector<int>() = {1000000000}, 2, 1);
    cout << r << endl;

    r = sol.minOperations(vector<int>() = {3, 4, 1, 7, 6}, 4, 2);
    cout << r << endl;
}