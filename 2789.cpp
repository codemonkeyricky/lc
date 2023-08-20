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
    long long maxArrayValue(vector<int> &nums)
    {
        long long rv = 0, n = 0;
        for (int i = nums.size() - 1; i >= 0; --i)
        {
            if (n >= nums[i])
                n += nums[i];
            else
                n = nums[i];
            if (n > rv)
                rv = n;
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.maxArrayValue(vector<int>() = {2, 3, 7, 9, 3});
    cout << r << endl;
}