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
    vector<int> smallerNumbersThanCurrent(vector<int> &nums)
    {
        vector<array<int, 2>> nums2;
        for (auto i = 0; i < nums.size(); ++i)
            nums2.push_back({nums[i], i});

        sort(begin(nums2), end(nums2));
        vector<int> rv(nums2.size());
        for (auto i = 0, j = 0; j < nums2.size(); ++j)
        {
            if (j && nums2[j][0] != nums2[j - 1][0])
                i = j;
            rv[nums2[j][1]] = i;
        }

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    sol.smallerNumbersThanCurrent(vector<int>() = {8, 1, 2, 2, 3});
    cout << r << endl;
}