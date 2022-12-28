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
    int maxJump(vector<int> &stones)
    {
        if (stones.size() == 2)
            return stones[1];

        int n = stones.size();
        vector<int> color(n);
        int i = 0;
        for (; i < n; i += 2)
            ++color[i];

        int p = -1; 
        int rv = 0;
        for (i = 0; i < n; ++i)
            if (color[i])
            {
                if (p != -1)
                    rv = max(rv, stones[i] - stones[p]);
                p = i;
            }

        for (i = n - 1; i >= 0; --i)
            if (!color[i])
            {
                rv = max(rv, stones[p] - stones[i]);
                p = i;
            }

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.maxJump(vector<int>() = {0, 1, 2, 3});
    cout << r << endl;

    r = sol.maxJump(vector<int>() = {0, 2, 5, 6, 7});
    cout << r << endl;
}