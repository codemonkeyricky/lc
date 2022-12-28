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
    bool checkStraightLine(vector<vector<int>> &coord)
    {
        sort(begin(coord), end(coord));
        int n = coord.size();
        int mx = 0, my = 0;
        for (auto i = 0; i < n; ++i)
            for (auto j = i + 1; j < n; ++j)
            {
                auto x = coord[i][0] - coord[j][0];
                auto y = coord[i][1] - coord[j][1];
                auto g = __gcd(x, y);
                if (mx == 0)
                    mx = x / g, my = y / g;
                if (mx != x / g || my != y / g)
                    return false;
            }

        return true;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}