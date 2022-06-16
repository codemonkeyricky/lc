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
    vector<int> getMaximumXor(vector<int> &nums, int maximumBit)
    {
        int sum = accumulate(begin(nums), end(nums), 0, [](int sum, const int &n)
                             { return sum ^ n; });

        int mask = (1 << maximumBit) - 1;
        vector<int> rv;
        for (int i = nums.size() - 1; i >= 0; --i)
        {
            int k = ~(sum & mask) & mask;
            rv.push_back(k);
            sum ^= nums[i];
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    sol.getMaximumXor(vector<int>() = {0, 1, 1, 3}, 2);
}