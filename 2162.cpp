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

using v = vector<int>;
using vv = vector<vector<int>>;

class Solution
{
    int dfs(int startAt, int moveCost, int pushCost, int target, int k = 0)
    {
        if (k >= 4)
            return target ? 1e9 : 0;

        int rv = 1e9;
        for (auto i = 0; i < 10; ++i)
        {
            int left;
            if (k == 0)
                left = target - i * 60 * 10;
            else if (k == 1)
                left = target - i * 60;
            else if (k == 2)
                left = target - i * 10;
            else if (k == 3)
                left = target - i;

            if (left >= 0)
                rv = min(rv, (startAt != i ? moveCost : 0) + pushCost + dfs(i, moveCost, pushCost, left, k + 1));
        }
        return rv;
    }

public:
    int minCostSetTime(int startAt, int moveCost, int pushCost, int target)
    {
        int rv = 1e9;
        for (auto i = 0; i < 4; ++i)
            rv = min(rv, dfs(startAt, moveCost, pushCost, target, i));
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minCostSetTime(0, 1, 2, 76);
    cout << r << endl;

    r = sol.minCostSetTime(1, 2, 1, 600);
    cout << r << endl;
}