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
    int getMaximumGenerated(int n)
    {
        if (n == 0)
            return 0;

        if (n == 1)
            return 1;

        vector<int> rv = {0, 1};
        int rrv = 0;
        for (auto i = 2; i < n + 1; ++i)
        {
            if (i % 2)
                rv.push_back(rv[i / 2] + rv[i / 2 + 1]);
            else
                rv.push_back(rv[i / 2]);

            rrv = max(rrv, rv.back());
        }

        return rrv; 
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.getMaximumGenerated(3);
    cout << r << endl;
}