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
    long long minOperations(vector<int> &nums1, vector<int> &nums2, int k)
    {
        if (!k)
            return nums1 == nums2 ? 0 : -1;

        long long rv = 0, n = nums1.size(), m = 0;
        for (auto i = 0; i < n; ++i)
            if ((nums1[i] - nums2[i]) % k != 0)
                return -1;
            else
            {
                rv += abs(nums1[i] - nums2[i]) / k;
                m += (nums1[i] - nums2[i]) / k;
            }
        return !m ? rv / 2 : -1;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}