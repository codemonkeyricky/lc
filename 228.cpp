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
    vector<string> summaryRanges(vector<int> &nums)
    {
        vector<string> rv;
        for (auto i = 0, j = 1; j <= nums.size(); ++j)
            if (j == nums.size() || nums[j - 1] + 1 != nums[j])
            {
                if (i == j - 1)
                    rv.push_back(to_string(nums[i]));
                else
                    rv.push_back(to_string(nums[i]) + "->" + to_string(nums[j - 1]));
                i = j;
            }

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    sol.summaryRanges(vector<int>() = {0, 1, 2, 4, 5, 7});
}