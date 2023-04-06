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
    bool isValid(int n, unordered_set<int> &masks)
    {
        if (masks.size() != 2)
            return false;

        int k1 = *(begin(masks));
        int k2 = *(next(begin(masks)));

        if (!(__builtin_popcount(k1) == (n / 2) && __builtin_popcount(k2) == ((n + 1) / 2)) 
         && !(__builtin_popcount(k2) == (n / 2) && __builtin_popcount(k1) == ((n + 1) / 2)))
            return false;

        if ((k1 ^ k2) != ((1 << n) - 1))
            return false;

        return true;
    }

    int count(int n, unordered_set<int> &uniq)
    {
        int row = *begin(uniq);
        int rv = 1e9;
        int limit = (1 << n) - 1;
        if (n % 2 == 0 || __builtin_popcount(row) * 2 < n)
            rv = min(rv, __builtin_popcount(row ^ (0xAAAAAAAA & limit)) / 2);
        if (n % 2 == 0 || __builtin_popcount(row) * 2 > n)
            rv = min(rv, __builtin_popcount(row ^ (0x55555555 & limit)) / 2);

        return rv;
    }

public:
    int movesToChessboard(vector<vector<int>> &board)
    {
        int n = board.size();
        vector<int> rows(n), cols(n);
        for (auto i = 0; i < n; ++i)
            for (auto j = 0; j < n; ++j)
                if (board[i][j])
                    rows[i] |= (1 << j);

        unordered_set<int> uniq_rows;
        for (auto &r : rows)
            uniq_rows.insert(r);

        if (!isValid(n, uniq_rows))
            return -1;

        for (auto j = 0; j < n; ++j)
            for (auto i = 0; i < n; ++i)
                if (board[i][j])
                    cols[j] |= (1 << i);

        unordered_set<int> uniq_cols;
        for (auto &c : cols)
            uniq_cols.insert(c);

        if (!isValid(n, uniq_cols))
            return -1;

        return count(n, uniq_rows) + count(n, uniq_cols);
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.movesToChessboard(vector<vector<int>>() =
                                  {{1, 1, 0},
                                   {0, 0, 1},
                                   {0, 0, 1}});
    cout << r << endl;


    r = sol.movesToChessboard(vector<vector<int>>() =
                                  {{0, 1},
                                   {1, 0}});
    cout << r << endl;

    r = sol.movesToChessboard(vector<vector<int>>() =
                                  {{0, 1, 1, 0},
                                   {0, 1, 1, 0},
                                   {1, 0, 0, 1},
                                   {1, 0, 0, 1}});
    cout << r << endl;
}