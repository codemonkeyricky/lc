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
    int xorBeauty(vector<int> &nums)
    {
        array<int, 32> bits = {};
        for (auto &n : nums)
            for (auto i = 0; i < 32; ++i)
                if (n & (1 << i))
                    ++bits[i];

        vector<int> to_xor;
        for (auto &n : nums)
        {
            int v = 0;
            for (auto i = 0; i < 32; ++i)
                if (n & (1 << i))
                    if (bits[i] % 2)
                        v |= 1 << i;
            to_xor.push_back(v);
        }

        return accumulate(begin(to_xor), end(to_xor), 0, bit_xor<void>());
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.xorBeauty(vector<int>() = {15, 45, 20, 2, 34, 35, 5, 44, 32, 30});
    cout << r << endl;

    r = sol.xorBeauty(vector<int>() = {1, 4});
    cout << r << endl;
}