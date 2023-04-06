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
    int waysToReachTarget(int target, vector<vector<int>> &types)
    {
        vector<long> prev(target + 1);
        prev[0] = 1;
        for (auto &t : types)
        {
            auto count = t[0], mark = t[1];
            auto curr = prev;
            for (auto i = 1; i <= count; ++i)
                for (int j = i * mark; j <= target; ++j)
                    curr[j] = (curr[j] + prev[j - i * mark]) % 1000000007;

            swap(curr, prev);
        }
        return prev[target];
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.waysToReachTarget(6, vector<vector<int>>() = {{6, 1}, {3, 2}, {2, 3}});
    cout << r << endl;
}