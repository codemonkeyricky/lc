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
    int countWays(vector<vector<int>> &ranges)
    {
        sort(begin(ranges), end(ranges));

        int n = ranges.size(), power = 0, right = ranges[0][1];
        for (auto i = 1; i < n; ++i)
        {
            if (right < ranges[i][0])
                ++power;
            right = max(right, ranges[i][1]);
        }

        int rv = 2;
        while (power)
            rv = (rv * 2) % 1000000007, --power;
    
        return rv; 
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.countWays(vector<vector<int>>() = {{34, 56}, {28, 29}, {12, 16}, {11, 48}, {28, 54}, {22, 55}, {28, 41}, {41, 44}});
    cout << r << endl;

    r = sol.countWays(vector<vector<int>>() = {{1, 2}, {1, 1}, {0, 4}});
    cout << r << endl;
}