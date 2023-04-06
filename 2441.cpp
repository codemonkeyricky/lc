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
    int findMaxK(vector<int> &nums)
    {
        sort(begin(nums), end(nums));
        int i = 0, j = nums.size() - 1;
        while (i < j && nums[i] < 0 && nums[j] > 0)
            if (abs(nums[i]) == nums[j])
                return nums[j];
            else if (abs(nums[i]) < nums[j])
                --j;
            else
                ++i;
        return -1;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.findMaxK(vector<int>() = {-1, 2, -3, 3});
    cout << r << endl;
}