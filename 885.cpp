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
    vector<vector<int>> spiralMatrixIII(int m, int n, int i, int j)
    {
        vector<int> off = {0, -1, 0, 1, 0};
        int l = 1, k = 0, len = 0;
        vector<vector<int>> rv = {{i, j}};
        while (len <= max(m, n) + 2)
        {
            if (k && k % 2 == 0)
                ++len;

            for (auto l = 0; l < len; ++l)
            {
                auto ni = i + off[k % 4 + 0];
                auto nj = j + off[k % 4 + 1];
                if (ni >= 0 && ni < m && nj >= 0 && nj < n)
                    rv.push_back({ni, nj});
                i = ni, j = nj;
            }

            ++k;
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    sol.spiralMatrixIII(5, 6, 1, 4);
    cout << r << endl;

    sol.spiralMatrixIII(1, 4, 0, 0);
    cout << r << endl;
}