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
    int minimumLines(vector<vector<int>> &p)
    {
        int rv = 0, dx = INT_MIN, dy = INT_MIN;
        sort(begin(p), end(p));
        for (int i = 1; i < p.size(); ++i)
        {
            int dx1 = p[i][0] - p[i - 1][0]; 
            int dy1 = p[i][1] - p[i - 1][1];
            int d = gcd(dx1, dy1);
            rv += dx != dx1 / d || dy != dy1 / d;
            dx = dx1 / d;
            dy = dy1 / d;
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minimumLines(vector<vector<int>>() = {{72, 98}, {62, 27}, {32, 7}, {71, 4}, {25, 19}, {91, 30}, {52, 73}, {10, 9}, {99, 71}, {47, 22}, {19, 30}, {80, 63}, {18, 15}, {48, 17}, {77, 16}, {46, 27}, {66, 87}, {55, 84}, {65, 38}, {30, 9}, {50, 42}, {100, 60}, {75, 73}, {98, 53}, {22, 80}, {41, 61}, {37, 47}, {95, 8}, {51, 81}, {78, 79}, {57, 95}});
    cout << r << endl;
}