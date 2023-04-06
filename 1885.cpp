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
    vector<int> bit;

    void update(int k, int v)
    {
        for (k += 100001; k < 200002; k += k & -k)
            bit[k] += v;
    }

    int get(int k)
    {
        int rv = 0;
        for (k += 100001; k; k -= k & -k)
            rv += bit[k];
        return rv;
    }

public:
    long long countPairs(vector<int> &nums1, vector<int> &nums2)
    {
        int n = nums1.size();

        bit = vector<int>(200002);

        for (auto i = 0; i < n; ++i)
            update(nums1[i] - nums2[i], 1);

        long long rv = 0;
        for (auto i = 0; i < nums1.size(); ++i)
        {
            update(nums1[i] - nums2[i], -1);
            rv += (long long)(i - get(nums2[i] - nums1[i] ));
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.countPairs(vector<int>() = {2, 1, 2, 1}, vector<int>() = {1, 2, 1, 2});
    cout << r << endl;
}