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
    long long minimumTotalCost(vector<int> &nums1, vector<int> &nums2)
    {
        long long rv = 0;
        vector<int> counts(100001, 0);
        int dominant = 0;
        int dominantNum = -1;
        int involvedCnt = 0;
        int n = nums1.size();
        for (int i = 0; i < n; ++i)
            if (nums1[i] == nums2[i])
            {
                rv += i;
                ++counts[nums1[i]];
                if (counts[nums1[i]] > dominant)
                {
                    dominant = counts[nums1[i]];
                    dominantNum = nums1[i];
                }
                ++involvedCnt;
            }

        if (dominant > involvedCnt / 2)
        {
            for (int i = 0; i < n; ++i)
            {
                if (nums1[i] != nums2[i] && nums1[i] != dominantNum && nums2[i] != dominantNum)
                {
                    ++counts[nums1[i]];
                    ++involvedCnt;
                    rv += i;
                    if (dominant <= involvedCnt / 2)
                    {
                        return rv;
                    }
                }
            }
            return -1;
        }
        else
        {
            return rv;
        }
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minimumTotalCost(vector<int>() = {1, 2, 3, 4}, vector<int>() = {4, 2, 3, 4});
    cout << r << endl;

    r = sol.minimumTotalCost(vector<int>() = {2, 1, 2, 2, 1, 4, 1, 5}, vector<int>() = {2, 1, 2, 2, 1, 4, 1, 5});
    cout << r << endl;

    r = sol.minimumTotalCost(vector<int>() = {4, 2, 3, 2, 2, 2, 2, 5, 4, 4}, vector<int>() = {4, 2, 3, 2, 2, 2, 2, 5, 4, 4});
    cout << r << endl;

    r = sol.minimumTotalCost(vector<int>() = {1, 2, 2}, vector<int>() = {1, 2, 2});
    cout << r << endl;

    r = sol.minimumTotalCost(vector<int>() = {2, 2, 2, 1, 3}, vector<int>() = {1, 2, 2, 3, 3});
    cout << r << endl;

    r = sol.minimumTotalCost(vector<int>() = {1, 2, 3, 4, 5}, vector<int>() = {1, 2, 3, 4, 5});
    cout << r << endl;
}