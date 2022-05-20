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
    int largestCombination(vector<int> &candidates)
    {
        array<int, 32> bits = {};
        for (auto &c : candidates)
            for (auto i = 0; i < 32; ++i)
                if (c & (1 << i))
                    ++bits[i];
        
        int rv = 0;
        for (auto i = 0; i < 32; ++i)
            rv = max(rv, bits[i]);
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.largestCombination(vector<int>() = {33, 93, 31, 99, 74, 37, 3, 4, 2, 94, 77, 10, 75, 54, 24, 95, 65, 100, 41, 82, 35, 65, 38, 49, 85, 72, 67, 21, 20, 31});
    cout << r << endl;

    r = sol.largestCombination(vector<int>() = {16, 17, 71, 62, 12, 24, 14});
    cout << r << endl;
}