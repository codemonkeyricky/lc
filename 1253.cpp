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
    vector<vector<int>> reconstructMatrix(int upper, int lower, vector<int> &colsum)
    {
        int n = colsum.size();
        vector<vector<int>> rv(2, vector<int>(n));
        for (auto i = 0; i < n; ++i)
        {
            if (colsum[i] == 2)
                if (upper == 0 || lower == 0)
                    return {};
                else
                    rv[0][i] = rv[1][i] = 1, --upper, --lower;
            else if (colsum[i] == 1)
                if (upper >= lower)
                    if (upper == 0)
                        return {};
                    else
                        rv[0][i] = 1, --upper;
                else
                {
                    if (lower == 0)
                        return {};
                    else
                        rv[1][i] = 1, --lower;
                }
        }
        if (lower == 0 && upper == 0)
            return rv;
        return {};
    }
};

int main()
{
    Solution sol;
    int r;

    sol.reconstructMatrix(4, 7, vector<int>() = {2, 1, 2, 2, 1, 1, 1});
    cout << r << endl;

    sol.reconstructMatrix(2, 1, vector<int>() = {1, 1, 1});
    cout << r << endl;
}