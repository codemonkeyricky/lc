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
    int minHeightShelves(vector<vector<int>> &books, int width)
    {
        int n = books.size();
        vector<int> dp(n, 1e9);
        for (auto j = 0, w = 0, h = 0; j < n; ++j, w = 0, h = 0)
        {
            for (int i = j; i >= 0 && w + books[i][0] <= width; --i)
            {
                h = max(h, books[i][1]);
                dp[j] = min(dp[j], h + (i ? dp[i - 1] : 0));
                w += books[i][0];
            }
        }

        return dp[n - 1];
    }
};

int main()
{
    Solution sol;
    int r;

    // r = sol.minHeightShelves(vector<vector<int>>() = {{1, 3}, {2, 4}, {3, 2}}, 6);
    // cout << r << endl;

    r = sol.minHeightShelves(vector<vector<int>>() = {{1, 1}, {2, 3}, {2, 3}, {1, 1}, {1, 1}, {1, 1}, {1, 2}}, 4);
    cout << r << endl;
}