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
    int maxNumberOfAlloys(int n, int k, int budget, vector<vector<int>> &composition, vector<int> &stock, vector<int> &cost)
    {
        long rv = 0;
        for (auto i = 0; i < k; ++i)
        {
            long l = 0, r = 1e9;
            while (l < r)
            {
                long c = 0;
                long m = (l + r + 1) / 2;
                for (auto j = 0; j < composition[i].size(); ++j)
                    if (stock[j] < composition[i][j] * m)
                        c += (long)cost[j] * (composition[i][j] * m - stock[j]);

                if (c <= budget)
                    l = m;
                else
                    r = m - 1;
            }
            rv = max(rv, l);
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.maxNumberOfAlloys(3, 2, 15, vector<vector<int>>() = {{1, 1, 1}, {1, 1, 10}}, vector<int>() = {0, 0, 100}, vector<int>() = {1, 2, 3});
    cout << r << endl;

    r = sol.maxNumberOfAlloys(3, 2, 15, vector<vector<int>>() = {{1, 1, 1}, {1, 1, 10}}, vector<int>() = {0, 0, 0}, vector<int>() = {1, 2, 3});
    cout << r << endl;
}