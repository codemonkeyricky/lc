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
    vector<vector<int>> differenceOfDistinctValues(vector<vector<int>> &g)
    {
        int m = g.size(), n = g[0].size();
        vector<vector<int>> rv(m, vector<int>(n));
        auto populateDiag = [&](int i, int j)
        {
            unordered_set<int> tl, br;
            int d = 0;
            for (; i + d < m && j + d < n; ++d)
            {
                rv[i + d][j + d] = tl.size();
                tl.insert(g[i + d][j + d]);
            }
            for (d = d - 1; d >= 0; --d)
            {
                rv[i + d][j + d] = abs(rv[i + d][j + d] - (int)br.size());
                br.insert(g[i + d][j + d]);
            }
        };
        for (int j = 0; j < n; ++j)
            populateDiag(0, j);
        for (int i = 1; i < m; ++i)
            populateDiag(i, 0);
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}