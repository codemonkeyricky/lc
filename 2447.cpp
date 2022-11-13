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
    int subarrayGCD(vector<int> &nums, int k)
    {
        int rv = 0;
        int n = nums.size();
        for (auto i = 0; i < n; ++i)
            for (auto j = i, d = nums[j]; j < n; ++j)
            {
                d = gcd(d, nums[j]);
                if (d == k)
                    ++rv;
                else if (d < k)
                    break;
            }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.subarrayGCD(vector<int>() = {9, 3, 1, 2, 6, 3}, 3);
    cout << r << endl;
}