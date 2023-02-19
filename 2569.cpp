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
    void invert(int n, int l, int r, int i, int j)
    {
        if (lazy[n])
        {
            // node is within invert range
            tree[n] = (r - l + 1) - tree[n];

            // every node below need to be inverted because already in range.
            if (l != r)
            {
                lazy[n * 2] = !lazy[n * 2];
                lazy[n * 2 + 1] = !lazy[n * 2 + 1];
            }

            lazy[n] = 0;
        }

        // case 1: skip if region not of interest
        if (j < l || i > r)
            return;

        // case 2: in range
        if (i <= l && r <= j)
        {
            // node is within invert range
            tree[n] = (r - l + 1) - tree[n];

            // every node below need to be inverted because already in range.
            if (l != r)
            {
                lazy[n * 2] = !lazy[n * 2];
                lazy[n * 2 + 1] = !lazy[n * 2 + 1];
            }

            return;
        }

        // case 3:
        int m = (l + r) / 2;

        invert(n * 2, l, m, i, j);
        invert(n * 2 + 1, m + 1, r, i, j);

        tree[n] = tree[n * 2] + tree[n * 2 + 1];
    }

    int query(int n, int l, int r, int i, int j)
    {
        if (lazy[n])
        {
            // node is within invert range
            tree[n] = (r - l + 1) - tree[n];

            // every node below need to be inverted because already in range.
            if (l != r)
            {
                lazy[n * 2] = !lazy[n * 2];
                lazy[n * 2 + 1] = !lazy[n * 2 + 1];
            }

            lazy[n] = 0;
        }

        if (j < l || i > r)
            return 0 ;

        // node in range
        if (i <= l && r <= j)
            return tree[n];

        // case 3
        int m = (l + r) / 2;
        int p1 = query(n * 2, l, m, i, j);
        int p2 = query(n * 2 + 1, m + 1, r, i, j);
        return p1 + p2;
    }

    vector<int> tree, lazy;

public:
    vector<long long> handleQuery(vector<int> &n1, vector<int> &n2, vector<vector<int>> &queries)
    {
        int n = n1.size();
        tree = vector<int>(n * 3);
        lazy = vector<int>(n * 3);

        for (auto i = 0; i < n; ++i)
            if (n1[i])
                invert(1, 0, n - 1, i, i);

        long long sum = accumulate(begin(n2), end(n2), 0ll);
        vector<long long> rv; 
        for (auto &q : queries)
        {
            int type = q[0], l = q[1], r = q[2];
            if (type == 1)
                invert(1, 0, n - 1, l, r);
            else if (type == 2)
            {
                long long ones = query(1, 0, n - 1, 0, n - 1);
                sum += l * ones; 
            }
            else
                rv.push_back(sum);
        }
        return rv; 
    }
};

int main()
{
    Solution sol;
    vector<long long> r;

    r = sol.handleQuery(vector<int>() = {1, 0, 1},
                        vector<int>() = {44, 28, 35},        // 101
                        vector<vector<int>>() = {{1, 0, 1},  // 011 c
                                                 {2, 10, 0}, // 44, 38, 45
                                                 {2, 2, 0},  // 44, 40, 47
                                                 {2, 7, 0},  // 44, 47, 54
                                                 {3, 0, 0},
                                                 {3, 0, 0}, // --> 145
                                                 {1, 2, 2}, // 010
                                                 {1, 1, 2}, // 001
                                                 {2, 1, 0},
                                                 {1, 0, 2}, // 110
                                                 {1, 2, 2}, // 111
                                                 {1, 0, 2}, // 000
                                                 {3, 0, 0}, // --> 148
                                                 {1, 1, 2}, // 010
                                                 {3, 0, 0},
                                                 {1, 0, 1},
                                                 {2, 21, 0},
                                                 {1, 0, 1},
                                                 {2, 26, 0},
                                                 {1, 1, 1}});
    for (auto c : r)
        cout << c << ", ";
    cout << endl;

    sol.handleQuery(vector<int>() = {1, 0, 1},
                    vector<int>() = {0, 0, 0},
                    vector<vector<int>>() = {{1, 1, 1}, {2, 1, 0}, {3, 0, 0}});
    // cout << r << endl;
}