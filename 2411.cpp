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
    vector<int> smallestSubarrays(vector<int> &nums)
    {
        int n = nums.size();
        vector<array<int, 32>> indices(n);
        vector<int> masks(n); 
        for (int i = n - 1; i >= 0; --i)
        {
            if (i + 1 < n)
                indices[i] = indices[i + 1], masks[i] = masks[i + 1];
            int mask = nums[i];
            for (auto k = 0; k < 32; ++k)
                if ((1 << k) & mask)
                    indices[i][k] = i + 1;
            masks[i] |= nums[i];
        }

        vector<int> rv;
        for (auto i = 0, m = 0; i < n; ++i, m = i)
        {
            for (auto k = 0; k < 32; ++k)
                if ((1 << k) & masks[i])
                    m = max(m, indices[i][k] - 1);
            rv.push_back(m - i + 1);
        }
        return rv; 
    }
};

int main()
{
    Solution sol;
    vector<int> r;

    r = sol.smallestSubarrays(vector<int>() = {1, 0});

    r = sol.smallestSubarrays(vector<int>() = {0});

    r = sol.smallestSubarrays(vector<int>() = {1, 0, 2, 1, 3});
    // cout << r << endl;
}