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
    vector<int> createTargetArray(vector<int> &nums, vector<int> &index)
    {
        int n = nums.size();
        vector<int> rv;
        for (auto i = 0; i < n; ++i)
        {
            if (index[i] >= rv.size())
                rv.resize(index[i] + 1);
            rv.insert(begin(rv) + index[i], nums[i]);
        }

        rv.resize(n);

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    sol.createTargetArray(vector<int>() = {0, 1, 2, 3, 4}, vector<int>() = {0, 1, 2, 2, 1});
}