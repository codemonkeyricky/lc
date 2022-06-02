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
    int minimumLines(vector<vector<int>> &points)
    {
        sort(begin(points), end(points));
        int n = points.size();
        set<array<int, 2>> slope;
        for (auto i = 0; i < n; ++i)
            for (auto j = i + 1; j < n; ++j)
                {
                    int dx = points[j][0] - points[i][0];
                    int dy = points[j][1] - points[i][1];
                    int d = gcd(dx, dy);
                    slope.insert({dx / d, dy / d});
                }

        return slope.size();
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}