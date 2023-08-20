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
    int sumDistance(vector<int> &nums, string s, int d)
    {
        auto n = nums.size();
        for (auto i = 0; i < n; ++i)
            nums[i] += (s[i] == 'L' ? -1 : 1) * d;
        sort(begin(nums), end(nums));

        long rv = 0, sum = 0, prev = 0;
        for (auto i = 1; i < n; ++i)
        {
            auto d = ((long)nums[i] - nums[i - 1]);
            sum = prev + d * i;
            rv = (rv + sum) % 1000000007;
            prev = sum;

        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.sumDistance(vector<int>() = {-10, -13, 10, 14, 11}, "LRLLR", 2);
    cout << r << endl;

    r = sol.sumDistance(vector<int>() = {-2, 0, 2}, "RLL", 3);
    cout << r << endl;
}