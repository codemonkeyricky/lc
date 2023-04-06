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
    const double tol = 1e-6;
    double R;

    struct Point
    {
        double x, y;
    };

    vector<Point> point;

    double dis(const Point &a, const Point &b)
    {
        return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    }

    array<Point, 2> getCenter(const Point &a, const Point &b)
    {
        Point mid;
        array<Point, 2> rv = {};
        mid.x = (a.x + b.x) / 2, mid.y = (a.y + b.y) / 2;
        double theta = atan2(a.y - b.y, b.x - a.x);
        double tmp = dis(a, b) / 2;
        double d = sqrt(R * R - tmp * tmp);
        rv[0].x = mid.x - d * sin(theta);
        rv[0].y = mid.y - d * cos(theta);
        rv[1].x = mid.x + d * sin(theta);
        rv[1].y = mid.y + d * cos(theta);
        return rv;
    }

public:
    int numPoints(vector<vector<int>> &points, int r)
    {
        /* Maximum Number of Darts Inside of a Circular Dartboard */
        int n = points.size();
        R = (double)r;
        point.resize(n);
        for (int i = 0; i < n; ++i)
            point[i].x = points[i][0], point[i].y = points[i][1];

        int rv = 1;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (i != j && dis(point[i], point[j]) - 2 * R <= tol)
                {
                    int cnt = 0;
                    auto p = getCenter(point[i], point[j]);
                    for (auto k = 0, cnt = 0; k < 2; rv = max(rv, cnt), ++k, cnt = 0)
                        for (int l = 0; l < n; l++)
                            if (dis(point[l], p[0]) - R <= tol)
                                cnt++;
                }
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