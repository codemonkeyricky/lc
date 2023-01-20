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
    int mirrorReflection(int p, int q)
    {
        int lcm = std::lcm(p, q);
        auto k = lcm / p;
        if (k % 2 == 0)
            return 0;

        if ((lcm / q) % 2 == 0)
            return 2;

        return 1;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << sol.mirrorReflection(3, 2) << endl;
    cout << sol.mirrorReflection(3, 1) << endl;
    cout << sol.mirrorReflection(2, 1) << endl;
}