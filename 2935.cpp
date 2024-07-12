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
    int BITS = 20;

    void insert(int n, int k)
    {
        if (k * 2 < tree.size())
        {
            int index = log2(k);
            int bit = BITS - index - 1;
            ++tree[k];
            if (bit >= 0)
                insert(n, k * 2 + ((n & (1 << bit)) ? 1 : 0));
        }
    }

    void remove(int n, int k)
    {
        if (k * 2 < tree.size())
        {
            int index = log2(k);
            int bit = BITS - index - 1;
            --tree[k];
            if (bit >= 0)
                remove(n, k * 2 + ((n & (1 << bit)) ? 1 : 0));
        }
    }

    int maxXor(int n, int k)
    {
        if (k * 2 < tree.size())
        {
            int index = log2(k);
            int bit = BITS - index - 1;

            if (bit < 0)
                return 0;

            int b = 1 << bit;
            int bb = (n & b) > 0;

            if (tree[k * 2 + !bb])
                return b + maxXor(n, k * 2 + !bb);
            else 
                return maxXor(n, k * 2 + bb);
        }
        return 0;
    }

    vector<int> tree;

public:
    int maximumStrongPairXor(vector<int> &nums)
    {
        sort(begin(nums), end(nums));

        tree = vector<int>((1 << (BITS + 2)));

        int n = nums.size(), rv = 0;
        for (auto i = 0, j = 0; j < n; ++j)
        {
            insert(nums[j], 1);
            while (nums[i] * 2 < nums[j])
                remove(nums[i++], 1);

            rv = max(rv, maxXor(nums[j], 1));
        }

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.maximumStrongPairXor(vector<int>() = {500, 520, 2500, 3000});
    cout << r << endl;

    r = sol.maximumStrongPairXor(vector<int>() = {10, 100});
    cout << r << endl;

    r = sol.maximumStrongPairXor(vector<int>() = {3, 4});
    cout << r << endl;
}