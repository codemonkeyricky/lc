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
    int maximumsSplicedArray(vector<int> &nums1, vector<int> &nums2)
    {
        int maxSoFar = 0, sum = 0;
        for (auto i = 0; i < nums1.size(); ++i)
        {
            if (sum + nums2[i] > nums1[i])
                sum += nums2[i] - nums1[i];
            else
                sum = 0;
            maxSoFar = max(maxSoFar, sum);
        }

        int maxSoFar2 = 0;
        sum = 0;
        for (auto i = 0; i < nums2.size(); ++i)
        {
            if (sum + nums1[i] > nums2[i])
                sum += nums1[i] - nums2[i];
            else
                sum = 0;
            maxSoFar2 = max(maxSoFar2, sum);
        }

        auto sum1 = accumulate(begin(nums1), end(nums1), 0);
        auto sum2 = accumulate(begin(nums2), end(nums2), 0);
        return max(sum1 + maxSoFar, sum2 + maxSoFar2);
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.maximumsSplicedArray(vector<int>() = {60, 60, 60}, vector<int>() = {10, 90, 10});
    cout << r << endl;
}