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
    int numberOfGoodSubarraySplits(vector<int> &nums)
    {
        auto sum = accumulate(begin(nums), end(nums), 0l);
        if (sum == 0)
            return 0;

        int j = nums.size() - 1;
        while (j >= 0 && nums[j] == 0)
            --j;
        int i = 0;
        while (i < nums.size() && nums[i] == 0)
            ++i;

        long rv = 1, zeros = 1;
        while (i <= j)
            if (nums[i++] == 1)
                rv = (rv * zeros) % 1000000007, zeros = 1;
            else
                ++zeros;
        
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.numberOfGoodSubarraySplits(vector<int>() = {0, 0, 1, 1});
    cout << r << endl;

    r = sol.numberOfGoodSubarraySplits(vector<int>() = {0, 1, 0, 0, 1});
    cout << r << endl;
}