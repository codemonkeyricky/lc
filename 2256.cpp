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
    int minimumAverageDifference(vector<int> &nums)
    {
        long  first = 0;
        long second = accumulate(begin(nums), end(nums), 0LL);
        array<int, 2> rv = {(int)1e9, -1};
        int n = nums.size();
        for (auto i = 0; i < nums.size(); ++i)
        {
            first += nums[i];
            second -= nums[i];
            int d = abs(first / (i + 1) - (i + 1 < n ? second / (n - i - 1) : 0));
            if (d < rv[0])
                rv[0] = d, rv[1] = i;
        }
        return rv[1];
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minimumAverageDifference(vector<int>() = {4, 2, 0});
    cout << r << endl;

    r = sol.minimumAverageDifference(vector<int>() = {0, 1, 0, 1, 0, 1});
    cout << r << endl;
}