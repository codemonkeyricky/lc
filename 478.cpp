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
    double RAD, XC, YC;
    Solution(double radius, double x_center, double y_center)
    {
        RAD = radius;
        XC = x_center;
        YC = y_center;
    }
    vector<double> randPoint()
    {
        double ang = (double)rand() / RAND_MAX * 2 * M_PI,
               hyp = sqrt((double)rand() / RAND_MAX) * RAD,
               adj = cos(ang) * hyp,
               opp = sin(ang) * hyp;
        return vector<double>{XC + adj, YC + opp};
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(radius, x_center, y_center);
 * vector<double> param_1 = obj->randPoint();
 */

int main()
{
    Solution sol(10, 1, 1);

    int n = 0;
    while (++n < 100)
        sol.randPoint();
}