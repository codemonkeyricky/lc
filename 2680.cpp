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
    long long maximumOr(vector<int> &nums, int kk)
    {
        int n = nums.size();
        long long rv = 0;
        array<int, 32> bits = {};
        for (auto n : nums)
        {
            int k = 0;
            while (n)
            {
                if (n & 1)
                    ++bits[k];
                ++k, n >>= 1;
            }
        }

        for (auto n : nums)
        {
            int k = 0;
            auto copy = bits;
            auto nn = n;
            while (n)
            {
                if (n & 1)
                    --copy[k];
                ++k, n >>= 1;
            }

            long long mask = 0;
            for (auto i = 0; i < 32; ++i)
                if (copy[i])
                    mask |= 1 << i;

            rv = max(rv, ((long long)nn << kk) | mask);
        }

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.maximumOr(vector<int>() = {12, 9}, 1);
    cout << r << endl;
}