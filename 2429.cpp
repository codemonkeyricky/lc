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
    int minimizeXor(int num1, int num2)
    {
        auto bits = __builtin_popcount(num2);

        vector<int> set, clear;
        for(auto i = 0; i < 32; ++i)
            if ((1 << i) & num1)
                set.push_back(i);
            else
                clear.push_back(i);

        reverse(begin(set), end(set));

        vector<int> to_set;
        for (auto i = 0; i < set.size() && bits; ++i, --bits)
            to_set.push_back(set[i]);

        for (auto i = 0; i < clear.size() && bits; ++i, --bits)
            to_set.push_back(clear[i]);
        
        int rv = 0;
        for (auto b : to_set)
            rv |= 1 << b;

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minimizeXor(3, 5);
    cout << r << endl;
}