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
    int xorAllNums(vector<int> &nums1, vector<int> &nums2)
    {
        int rv = 0;
        if (nums1.size() % 2)
            for (auto &n : nums2)
                rv ^= n;

        if (nums2.size() % 2)
            for (auto &n : nums1)
                rv ^= n;

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.xorAllNums(vector<int>() = {2, 1, 3}, vector<int>() = {10, 2, 5, 10});
    cout << r << endl;
}