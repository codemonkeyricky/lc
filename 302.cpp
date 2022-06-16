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
    void dfs(vector<vector<char>> &image, int i, int j, array<int,4> &box)
    {
        vector<int> off = {0, 1, 0, -1, 0};
        if (image[i][j] == '0' || image[i][j] == '2')
            return;

        int m = image.size();
        int n = image[0].size();
        image[i][j] = '2';

        box[0] = min(box[0], i);
        box[1] = min(box[1], j);
        box[2] = max(box[2], i);
        box[3] = max(box[3], j);

        for (auto k = 0; k < 4; ++k)
        {
            auto ni = i + off[k + 0];
            auto nj = j + off[k + 1];
            if (ni >= 0 && nj >= 0 && ni < m && nj < n)
                dfs(image, ni, nj, box);
        }
    }

public:
    int minArea(vector<vector<char>> &image, int x, int y)
    {
        array<int, 4> box = {INT_MAX, INT_MAX, 0, 0};
        dfs(image, x, y, box);
        return (box[2] - box[0] + 1) * (box[3] - box[1] + 1);
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}