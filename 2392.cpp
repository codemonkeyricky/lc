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
    bool dfs(vector<vector<int>> &al, int k, vector<int> &curr, vector<int> &seen)
    {
        if (seen[k] == 1)
            return false;

        if (seen[k] == 2)
            return true;

        seen[k] = 1;
        for (auto &n : al[k])
            if (!dfs(al, n, curr, seen))
                return false;

        curr.push_back(k);
        seen[k] = 2;
        return true;
    }

public:
    vector<vector<int>> buildMatrix(int k, vector<vector<int>> &rows, vector<vector<int>> &cols)
    {
        vector<vector<int>> al(k + 1);
        for (auto &r : rows)
            al[r[0]].push_back(r[1]);

        vector<int> row, seen(k + 1);
        for (auto &r : rows)
            if (!seen[r[0]])
                if (!dfs(al, r[0], row, seen))
                    return {};
        reverse(begin(row), end(row));

        al = vector<vector<int>>(k + 1);
        for (auto &c : cols)
            al[c[0]].push_back(c[1]);

        seen = vector<int>(k + 1);
        vector<int> col;
        for (auto &c : cols)
            if (!seen[c[0]])
                if (!dfs(al, c[0], col, seen))
                    return {};
        reverse(begin(col), end(col));

        vector<array<int, 2>> nums(k + 1);
        for (auto i = 0; i < row.size(); ++i)
            nums[row[i]][0] = i;

        for (auto j = 0; j < col.size(); ++j)
            nums[col[j]][1] = j;

        vector<vector<int>> rv(k, vector<int>(k));
        for (auto k = 1; k < nums.size(); ++k)
        {
            auto [i, j] = nums[k];
            rv[i][j] = k;
        }

        return rv;
    }
};

int main()
{
    Solution sol;
    vector<vector<int>> r;

    r = sol.buildMatrix(3, vector<vector<int>>() = {{1, 2}, {3, 2}}, vector<vector<int>>() = {{2, 1}, {3, 2}});
    for (auto &row : r)
    {
        for (auto &c : row)
            cout << c << " ";
        cout << endl;
    }
}