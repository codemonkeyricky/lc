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
    int maximizeSquareHoleArea(int n, int m, vector<int> &hBars, vector<int> &vBars)
    {
        sort(begin(hBars), end(hBars));
        sort(begin(vBars), end(vBars));

        int h = hBars.size() ? 1 : 0, hh = 1;
        for (int i = 1; i < hBars.size(); ++i)
            if (hBars[i] - hBars[i - 1] == 1)
                h = max(h, ++hh);
            else
                hh = 1;

        int v = vBars.size() ? 1 : 0, vv = 1;
        for (int i = 1; i < vBars.size(); ++i)
            if (vBars[i] - vBars[i - 1] == 1)
                v = max(v, ++vv);
            else
                vv = 1;

        int l = min(h, v) + 1;
        return l * l;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.maximizeSquareHoleArea(2, 1, vector<int>() = {2, 3}, vector<int>() = {2});
    cout << r << endl;
}