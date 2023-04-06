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
    int countQuadruplets(vector<int> &nums)
    {
        int n = nums.size(), rv = 0;
        for (auto i = 0; i < n; ++i)
            for (auto j = i + 1; j < n; ++j)
            {
                unordered_map<int, int> map;
                for (auto k = j + 1; k < n; ++k)
                    ++map[nums[k]];

                for (auto k = j + 1; k < n; ++k)
                {
                    --map[nums[k]];
                    if (map[nums[i] + nums[j] + nums[k]])
                        rv += map[nums[i] + nums[j] + nums[k]];
                }
            }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.countQuadruplets(vector<int>() = {28, 8, 49, 85, 37, 90, 20, 8});
    cout << r << endl;

    r = sol.countQuadruplets(vector<int>() = {1, 2, 3, 6});
    cout << r << endl;
}