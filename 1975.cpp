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
    long long maxMatrixSum(vector<vector<int>> &matrix)
    {
        int m = matrix.size();
        int n = matrix[0].size();
        long long sum = 0;
        int mmin = 1e9;
        int neg = 0;
        int zero = 0;
        for (auto i = 0; i < m; ++i)
            for (auto j = 0; j < m; ++j)
            {
                if (!matrix[i][j])
                    ++zero;

                sum += abs(matrix[i][j]);
                mmin = min(mmin, abs(matrix[i][j]));
                if (matrix[i][j] < 0)
                    ++neg;
            }

        return neg & 1 ? sum - abs(mmin) * 2 : sum;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.maxMatrixSum(vector<vector<int>>() = {{2, 9, 3}, {5, 4, -4}, {1, 7, 1}});
    cout << r << endl;
}