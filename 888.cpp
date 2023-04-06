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
    vector<int> fairCandySwap(vector<int> &aliceSizes, vector<int> &bobSizes)
    {
        auto alice = accumulate(begin(aliceSizes), end(aliceSizes), 0);
        auto total = alice + accumulate(begin(bobSizes), end(bobSizes), 0);
        unordered_set<int> bob(begin(bobSizes), end(bobSizes));

        for (auto &a : aliceSizes)
            if (bob.count(total / 2 - (alice - a)))
                return {a, total / 2 - (alice - a)};
        return {};
    }
};

int main()
{
    Solution sol;
    int r;

    sol.fairCandySwap(vector<int>() = {1, 1}, vector<int>() = {2, 2});
}