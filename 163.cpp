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
    vector<string> findMissingRanges(vector<int> &nums, int lower, int upper)
    {
        vector<int> stack = {lower - 1};
        vector<string> rv;
        for(auto k = 0; k <= nums.size(); ++k)
        {
            int n = k < nums.size() ? nums[k] : upper + 1;
            if (n - stack.back() == 2)
                rv.push_back(to_string(n - 1));
            else if (n - stack.back() > 2)
                rv.push_back(to_string(stack.back() + 1) + "->" + to_string(n - 1));
            stack.push_back(n);
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    sol.findMissingRanges(vector<int>() = {0, 1, 3, 50, 75}, 0, 99);
}