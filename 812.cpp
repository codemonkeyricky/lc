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
    double largestTriangleArea(vector<vector<int>> &points)
    {
        int n = points.size();
        double rv = 0;
        for (auto i = 0; i < n; ++i)
            for (auto j = i + 1; j < n; ++j)
                for (auto k = j + 1; k < n; ++k)
                {
                    int x1 = points[i][0]; 
                    int y1 = points[i][1]; 
                    int x2 = points[j][0]; 
                    int y2 = points[j][1]; 
                    int x3 = points[k][0]; 
                    int y3 = points[k][1];
                    double sum = x1 * y2 + x2 * y3 + x3 * y1 - y1 * x2 - y2 * x3 - y3 * x1;
                    rv = max(rv, sum / 2);
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