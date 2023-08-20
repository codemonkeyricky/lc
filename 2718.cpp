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
    long long matrixSumQueries(int n, vector<vector<int>> &queries)
    {
        long long rv = 0;
        vector<int> rows(n), cols(n);
        int row_cnt = 0, col_cnt = 0;
        for (int i = queries.size() - 1; i >= 0; --i)
        {
            auto isCol = queries[i][0];
            auto k = queries[i][1];
            auto val = queries[i][2];
            if (isCol)
            {
                if (!cols[k])
                    rv += val * (n - row_cnt); 
                cols[k] = 1, ++col_cnt;
            }
            else 
            {
                if (!rows[k])
                    rv += val * (n - col_cnt);
                rows[k] = 1, ++row_cnt;
            }
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}