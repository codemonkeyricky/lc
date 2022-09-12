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
    long long countSubarrays(vector<int> &nums)
    {
        long long rv = 0, n = nums.size();
        for (auto j = 0, k = 0; j < n; ++j)
            if (j && nums[j - 1] < nums[j])
                rv += ++k;
            else
                ++rv, k = 1;

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.countSubarrays(vector<int>() = {1, 3, 5, 4, 4, 6});
    cout << r << endl;
}