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
    int longestSubarray(vector<int> &nums)
    {
        int bits = 0;
        for (auto &n : nums)
            if (n > bits)
                bits = n;

        int rv = 0, r = 0;
        for (auto &n : nums)
        {
            if (n != bits)
                r = 0;
            else
                ++r;
            rv = max(rv, r);
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.longestSubarray(vector<int>() = {96317, 96317, 96317, 96317, 96317, 96317, 96317, 96317, 96317, 279979});
    cout << r << endl;

    r = sol.longestSubarray(vector<int>() = {100, 5, 5});
    cout << r << endl;

    r = sol.longestSubarray(vector<int>() = {1, 2, 3, 3, 2, 2});
    cout << r << endl;
}