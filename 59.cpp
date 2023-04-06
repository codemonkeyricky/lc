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
    vector<vector<int>> generateMatrix(int n)
    {
        vector<int> off = {0, 1, 0, -1, 0};
        vector<vector<int>> m(n, vector<int>(n));
        int v = 0;
        m[0][0] = ++v;
        for (auto i = 0, j = 0, k = 0, attempt = 0; attempt < 4; k = (k + 1) % 4)
        {
            while (true)
            {
                ++attempt;
                auto ni = i + off[k + 0];
                auto nj = j + off[k + 1];
                if (ni >= 0 && ni < n && nj >= 0 && nj < n && !m[ni][nj])
                    m[ni][nj] = ++v, i = ni, j = nj, attempt = 0;
                else
                    break;
            }
        }
        return m;
    }
};

int main()
{
    Solution sol;

    sol.generateMatrix(3);
}