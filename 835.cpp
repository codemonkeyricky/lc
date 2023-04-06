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
    int largestOverlap(vector<vector<int>> &img1, vector<vector<int>> &img2)
    {
        int n = img1.size();
        int rv = 0;
        for (int i = -n; i <= n; ++i)
            for (int j = -n, r = 0; j <= n; rv = max(rv, r), ++j, r = 0)
                for (int k = 0; k < n; ++k)
                    for (int l = 0; l < n; ++l)
                        if (i + k >= 0 && i + k < n && j + l >= 0 && j + l < n)
                            if (img2[k][l] && img1[i + k][j + l] == img2[k][l])
                                ++r;
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.largestOverlap(vector<vector<int>>() = {{1, 1, 0}, {0, 1, 0}, {0, 1, 0}}, vector<vector<int>>() = {{0, 0, 0}, {0, 1, 1}, {0, 0, 1}});
    cout << r << endl;
}