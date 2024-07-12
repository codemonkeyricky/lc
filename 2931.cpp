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
    long long maxSpending(vector<vector<int>> &values)
    {
        priority_queue<array<int, 3>> q; ///< value / row / index
        long long rv = 0;

        int m = values.size();
        int n = values[0].size();
        for (auto i = 0; i < m; ++i)
            q.push({values[i][0], i, 0});

        long long d = m * n;
        while (d)
        {
            auto [k, i, j] = q.top();
            q.pop();

            rv += d-- * k;
            if (j + 1 < n)
                q.push({values[i][j + 1], i, j + 1});
        }

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.maxSpending(vector<vector<int>>() = {{8, 5, 2}, {6, 4, 1}, {9, 7, 3}});
    cout << r << endl;
}