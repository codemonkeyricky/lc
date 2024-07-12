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
    int minOperations(vector<int> &nums1, vector<int> &nums2)
    {
        int n = nums1.size();

        auto copy1 = nums1;
        auto copy2 = nums2;

        int rv = -1, r = 0;
        int i;
        for (i = 0; i < n - 1; ++i)
        {
            int pass = false;
            for (auto k = 0; k < 2 && !pass; swap(nums1[i], nums2[i]), ++k)
                if (nums1[i] <= nums1[n - 1] && nums2[i] <= nums2[n - 1])
                    pass = true;
                else
                    ++r;
            if (!pass)
                break;
        }

        if (i >= n - 1)
            rv = r;

        nums1 = copy1, nums2 = copy2;
        swap(nums1[n - 1], nums2[n - 1]);
        r = 1;
        for (i = 0; i < n - 1; ++i)
        {
            int pass = false;
            for (auto k = 0; k < 2 && !pass; swap(nums1[i], nums2[i]), ++k)
                if (nums1[i] <= nums1[n - 1] && nums2[i] <= nums2[n - 1])
                    pass = true;
                else
                    ++r;
            if (!pass)
                break;
        }

        if (i >= n - 1)
            rv = min(r, rv);

        return rv;
    }

};

int main()
{
    Solution sol;
    int r;

    r = sol.minOperations(vector<int>() = {1, 5, 4}, vector<int>() = {2, 5, 3});
    cout << r << endl;

    r = sol.minOperations(vector<int>() = {2, 3, 4, 5, 9}, vector<int>() = {8, 8, 4, 4, 4});
    cout << r << endl;

    r = sol.minOperations(vector<int>() = {1, 2, 7}, vector<int>() = {4, 5, 3});
    cout << r << endl;
}