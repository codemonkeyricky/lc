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
    vector<vector<int>> rangeAddQueries(int n, vector<vector<int>> &queries)
    {
        vector<vector<int>> mat(n, vector<int>(n, 0));

        for (auto q : queries)
        {
            int r1 = q[0], c1 = q[1], r2 = q[2], c2 = q[3];

            mat[r1][c1] += 1;
            if (r2 + 1 < n && c2 + 1 < n)
                mat[r2 + 1][c2 + 1] += 1;
            if (r2 + 1 < n)
                mat[r2 + 1][c1] -= 1;
            if (c2 + 1 < n)
                mat[r1][c2 + 1] -= 1;
        }

        for (int i = 0; i < n; i++)
            for (int j = 1; j < n; j++)
                mat[i][j] += mat[i][j - 1];

        for (int i = 1; i < n; i++)
            for (int j = 0; j < n; j++)
                mat[i][j] += mat[i - 1][j];

        return mat;
    }
};

// class Solution
// {
//     vector<vector<int>> mat;

// public:
//     vector<vector<int>> rangeAddQueries(int n, vector<vector<int>> &queries)
//     {
//         vector<vector<int>> mat(n, vector<int>(n + 1));
//         for (auto &q : queries)
//         {
//             auto r0 = q[0], c0 = q[1];
//             auto r1 = q[2], c1 = q[3];
//             for (auto i = r0; i <= r1; ++i)
//                 ++mat[i][c0], --mat[i][c1 + 1];
//         }

//         vector<vector<int>> rv(n, vector<int>(n));
//         for (auto i = 0, sum = 0; i < n; ++i, sum = 0)
//             for (auto j = 0; j < n; ++j)
//             {
//                 sum += mat[i][j];
//                 rv[i][j] = sum;
//             }

//         return rv; 
//     }
// };

int main()
{
    Solution sol;
    vector<vector<int>> rv;

    sol.rangeAddQueries(3, vector<vector<int>>() = {{1, 1, 2, 2}, {0, 0, 1, 1}});

    sol.rangeAddQueries(2, vector<vector<int>>() = {{0, 0, 1, 1}});
}