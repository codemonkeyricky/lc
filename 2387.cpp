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
    int matrixMedian(vector<vector<int>> &grid)
    {
        int m = grid.size(), n = grid[0].size();
        int l = 0, r = 1e9;
        while (l < r)
        {
            int mid = (l + r + 1) / 2, cnt = 0;
            for (auto &row : grid)
                cnt += n - (lower_bound(begin(row), end(row), mid) - begin(row));

            if (cnt >= n * m / 2 + 1)
                l = mid;
            else
                r = mid - 1;
        }
        return l;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.matrixMedian(vector<vector<int>>() = {{1, 1, 2}, {2, 3, 3}, {1, 3, 4}});
    cout << r << endl;
}