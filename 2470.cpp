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
    int subarrayLCM(vector<int> &nums, int k)
    {
        int n = nums.size(), rv = 0;
        for (auto i = 0, l = nums[i]; i < n; l = nums[++i])
            for (auto j = i; j < n; ++j)
            {
                l = lcm(l, nums[j]);
                if (l == k)
                    ++rv;
                else if (l > k)
                    break;
            }
                
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.subarrayLCM(vector<int>() = {3, 6, 2, 7, 1}, 6);
    cout << r << endl;
}