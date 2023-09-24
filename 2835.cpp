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
    int borrow(vector<int> &bits, int bit)
    {
        if (bit >= 32)
            return -1e9;

        int k = bit;
        if (bits[bit])
            --bits[bit];
        else 
        {
            int r = borrow(bits, bit + 1);
            if (r < 0)
                return -1e9;
            bits[bit] += r;
            --bits[bit];
            ++_rv;
        }
        return 2;
    }

    int _rv;

public:
    int minOperations(vector<int> &nums, int target)
    {
        _rv = 0;

        sort(begin(nums),end(nums));

        vector<int> bits(32);

        int k = 0;
        for (auto i = 0; i < nums.size(); ++i)
        {
            while ((nums[i] & (1 << k)) == 0)
                ++k;
            ++bits[k];
        }

        int rv = 0, bit = 0;
        while (target)
        {
            if (target & (1 << bit))
            {
                if (bits[bit] == 0)
                {
                    int borrowed = borrow(bits, bit);
                    if (borrowed < 0)
                        return -1;
                    // bits[bit] += borrowed;
                }

                --bits[bit];
                target &= ~(1 << bit);
            }
            if (bit < 32)
                bits[bit + 1] += bits[bit] / 2;
            ++bit;
        }
        return _rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minOperations(vector<int>() = {1, 32, 1}, 35);
    cout << r << endl;

    r = sol.minOperations(vector<int>() = {1, 32, 1, 2}, 12);
    cout << r << endl;

    r = sol.minOperations(vector<int>() = {1, 2, 8}, 7);
    cout << r << endl;
}