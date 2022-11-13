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
    long long maximumSubarraySum(vector<int> &nums, int k)
    {
        vector<int> seen(100001);
        long long sum = 0, rv = 0;
        for (auto i = 0, j = 0; j <= nums.size(); ++j)
        {
            if (j - i == k)
                rv = max(rv, sum);

            if (j < nums.size())
            {
                while (seen[nums[j]])
                    sum -= nums[i], --seen[nums[i++]];

                sum += nums[j];
                ++seen[nums[j]];

                if (j - i >= k)
                    sum -= nums[i], --seen[nums[i++]];
            }
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.maximumSubarraySum(vector<int>() = {1, 5, 4, 2, 9, 9, 9}, 3);
    cout << r << endl;
}