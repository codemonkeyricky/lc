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
    int numTriplets(vector<int> &nums1, vector<int> &nums2)
    {
        unordered_map<long long, int> dp;
        for (auto i = 0; i < nums2.size(); ++i)
            ++dp[nums2[i] * nums2[i]];

        int rv = 0;
        for (auto i = 0; i < nums1.size(); ++i)
            for (auto j = i + 1; j < nums1.size(); ++j)
                rv += dp[(long)nums1[i] * nums1[j]];

        dp.clear();
        for (auto i = 0; i < nums1.size(); ++i)
            ++dp[nums1[i] * nums1[i]];

        for (auto i = 0; i < nums2.size(); ++i)
            for (auto j = i + 1; j < nums2.size(); ++j)
                rv += dp[nums2[i] * nums2[j]];
        
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}