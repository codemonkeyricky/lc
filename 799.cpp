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
    double champagneTower(int poured, int query_row, int query_glass)
    {
        vector<double> curr = {(double)poured};
        for (auto r = 0; r <= query_row; ++r)
        {
            vector<double> next(curr.size() + 1);
            for (auto c = 0; c < curr.size(); ++c)
            {
                if (curr[c] >= 1)
                {
                    auto spill = curr[c] - 1.0; 
                    curr[c] = 1;
                    next[c] += spill * 0.5, next[c + 1] += spill * 0.5;
                }

                if (query_row == r && query_glass == c)
                    return curr[c];
            }
            swap(curr, next);
        }

        return -1;
    }
};

int main()
{
    Solution sol;
    double r;

    cout << sol.champagneTower(5, 5, 1) << endl;
    cout << sol.champagneTower(100000009, 33, 17) << endl;
    cout << sol.champagneTower(2, 1, 1) << endl;
}