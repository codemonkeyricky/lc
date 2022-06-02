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
    int maxBuilding(int n, vector<vector<int>> &restrict)
    {
        sort(begin(restrict), end(restrict));
        vector<array<int, 2>> stack;
        int rv = 0, mh = 0;
        for (auto k = 0; k < restrict.size(); ++k)
        {
            int j = restrict[k][0] - 1;
            int i = stack.empty() ? 0 : stack.back()[0];
            int ih = stack.empty() ? -1 : stack.back()[1];

            mh = max(mh, ih + j - i);

            while (stack.size() && stack.back()[1] >= restrict[k][1])
                stack.pop_back();

            int attempt = stack.empty() ? restrict[k][0] - 1 : (restrict[k][0] - stack.back()[0] + stack.back()[1]);
            stack.push_back({restrict[k][0], min(restrict[k][1], attempt)});
        }

        return mh;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.maxBuilding(10, vector<vector<int>>() = {{5, 3}, {2, 5}, {7, 4}, {10, 3}});
    cout << r << endl;
}