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
    int intersect(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2)
    {
        int max_x1 = max(ax1, bx1);
        int min_x2 = min(ax2, bx2);
        int max_y1 = max(ay1, by1);
        int min_y2 = min(ay2, by2);
        if (max_x1 < min_x2 && max_y1 < min_y2)
            return (min_x2 - max_x1) * (min_y2 - max_y1);
        else
            return 0;
    }

public:
    int computeArea(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2)
    {
        int k = intersect(ax1, ay1, ax2, ay2, bx1, by1, bx2, by2);
        return (ax2 - ax1) * (ay2 - ay1) + (bx2 - bx1) * (by2 - by1) - k;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.computeArea(-3, 0, 3, 4, 0, -1, 9, 2);
    cout << r << endl;
}