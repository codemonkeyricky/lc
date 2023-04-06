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
    int minOperations(string s)
    {
        int n = s.size();
        int rv = 1e9, r = 0;

        for (auto k = 0, b = 0; k < 2; ++k, b = 1, r = 0)
        {
            for (auto i = 0; i < n; ++i, b = !b)
                r += s[i] != (b + '0');
            rv = min(rv, r);
        }
        return rv; 
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minOperations("10");
    cout << r << endl;

    r = sol.minOperations("0100");
    cout << r << endl;
}